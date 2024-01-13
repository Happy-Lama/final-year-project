from django.db import models
from django.utils import timezone

# Create your models here.
class TransformerData(models.Model):
    devUID = models.CharField(max_length=255)
    output_current = models.FloatField()
    output_voltage = models.FloatField()
    output_power = models.FloatField()
    output_reactive_power = models.FloatField()
    output_frequency = models.FloatField()
    timestamp = models.DateTimeField(default=timezone.now)
    
class TransformerLocationData(models.Model):
    devUID = models.CharField(max_length=255, primary_key=True)
    latitude = models.FloatField()
    longitude = models.FloatField()
    operational = models.BooleanField(default=True)