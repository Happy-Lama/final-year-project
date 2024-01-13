from django.views.decorators.csrf import csrf_exempt
from django.http import JsonResponse
import json
from .models import TransformerData, TransformerLocationData
from .serializers import TransformerDataSerializer, TransformerLocationDataSerializer
from django.utils import timezone
from django.db.models import Avg

@csrf_exempt
def index(request):
    if request.method == 'POST':
        try:
            # Extract JSON data from the request
            data = json.loads(request.body.decode('utf-8'))
            received_data = data.get('data', {})
            print("Received Data:", received_data)
            
            # check if transformer is registered
            transformer_location_data = TransformerLocationData.objects.values(('devUID'))
            print(transformer_location_data)
            # while true:
            #     pass
            print('Before for loop',received_data['devUID'])
            for location in transformer_location_data:   
                print(received_data['devUID'], location['devUID'])              
                if received_data['devUID'] == location['devUID']: 
                    print('After if in for loop',received_data['devUID'], location['devUID'])        
                    transformer_data = TransformerData(
                        devUID=received_data['devUID'],
                        output_current=received_data['output_current'],
                        output_voltage=received_data['output_voltage'],
                        output_power=received_data['output_power'],
                        output_reactive_power=received_data['output_reactive_power'],
                        output_frequency=received_data['output_frequency'],
                        timestamp=timezone.now(),
                    )
                    
                    transformer_data.save()

                    return JsonResponse({'message': 'Data received successfully'})
            return JsonResponse({'message': 'Unregistered Transformer'}, status=400)
        except json.JSONDecodeError:
            return JsonResponse({'error': 'Invalid JSON data'}, status=400)

    return JsonResponse({'error': 'Unsupported method'}, status=405)


def get_all_transformer_data(request):
    
    transformer_location_data = TransformerLocationData.objects.all()
    
    # get only transformer data for the registered ones
    transformer_data = TransformerData.objects.filter(devUID__in=transformer_location_data.values('devUID'))
    
    location_data = TransformerLocationDataSerializer(transformer_location_data, many=True)
    serializer = TransformerDataSerializer(transformer_data, many=True)
     
    # average values of the transformer parameters
    average_values = TransformerDataSerializer().get_average_values(transformer_data)
    
    # moving average values for the transformer parameters
    # Calculate moving average over the last 24 hours with a window of 15 minutes
    twenty_four_hours_ago = timezone.now() - timezone.timedelta(hours=24)
    moving_average_queryset = TransformerData.objects.filter(timestamp__gte=twenty_four_hours_ago, devUID__in=transformer_location_data.values('devUID'))

            
    # Calculate moving average with a window of 15 minutes
    moving_average_values = []
    fifteen_minutes_delta = timezone.timedelta(minutes=15)
    current_timestamp = twenty_four_hours_ago

    while current_timestamp <= timezone.now():
        # Filter data within the current 15-minute window
        window_start = current_timestamp - fifteen_minutes_delta
        window_end = current_timestamp
        window_data = moving_average_queryset.filter(timestamp__gte=window_start, timestamp__lt=window_end)

        # Calculate average values for the current window
        if window_data.exists():
            window_average_values = window_data.aggregate(
                Avg('output_current'),
                Avg('output_voltage'),
                Avg('output_power'),
                Avg('output_reactive_power'),
                Avg('output_frequency')
            )
            moving_average_values.append({
                'timestamp': current_timestamp,
                'average_values': window_average_values,
            })

        # Move to the next 15-minute window
        current_timestamp += fifteen_minutes_delta
    return JsonResponse({
        'transformer_data':serializer.data,
        'transformer_location_data': location_data.data,
        'average_values': average_values,
        'moving_average_values': moving_average_values,
        })
        
        
        
def register(request):
    if request.method == 'POST':
        request_data = request.POST
        transformer = TransformerLocationData(
            devUID=request_data['devUID'],
            latitude=request_data['latitude'],
            longitude=request_data['longitude'],
        )
        
        transformer.save()
        
        return JsonResponse({'message': 'Transformer Registered'}, status=200)
    else:
        return JsonResponse({'message': 'Method Not Allowed'}, status=405)