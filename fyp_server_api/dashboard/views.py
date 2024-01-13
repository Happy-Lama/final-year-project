from django.shortcuts import render
# from django.views.decorators.csrf import ensure_csrf_cookie
from django.middleware.csrf import get_token
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
# Create your views here.

def index(request):
    return JsonResponse({"message": "Hello"})


def get_csrf_token(request):
    csrf_token = get_token(request)
    return JsonResponse({ 'csrfToken': csrf_token})

# @csrf_exempt
def login(request):
    if request.method == 'POST':
        return JsonResponse({'response':request.POST})