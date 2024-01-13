from django.urls import path
from . import views

urlpatterns = [
    path('api/', views.index),
    path('transformers/', views.get_all_transformer_data),
    path('transformers/register/', views.register)
]