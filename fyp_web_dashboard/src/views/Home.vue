<template>
  <MapComponent :transformers="transformers"/>
</template>

<script setup>
import MapComponent from '@/components/MapComponent.vue';
import { useAppStore } from '@/store/app';
import { onMounted, onUnmounted } from 'vue';
import { ref } from 'vue';
import { get_latest_transformer_data } from '@/httpservice';
import { watch } from 'vue';

const appStore = useAppStore()

const transformers = ref([]);

function updateLatestValues(newVal){
  console.log(newVal)
  if(newVal){}
  let transformers_data = []
  let transformer_devUIDs = []
  newVal.forEach((transformer) => {
    let formatted_data = {
      devUID: transformer['devUID'],
      data: {
        output_current: transformer['output_current'],
        output_voltage: transformer['output_voltage'],
        output_power: transformer['output_power'],
      },
      location: {}
    }

    for( let i = 0; i < appStore.transformer_location_data.length; i++){
      if(transformer['devUID'] === appStore.transformer_location_data[i]['devUID']){
        formatted_data.location = {
          position: [appStore.transformer_location_data[i]['latitude'], appStore.transformer_location_data[i]['longitude']],
          operational: appStore.transformer_location_data[i]['operational']
        }
      }
    }

    transformers_data.push(formatted_data)
    transformer_devUIDs.push(transformer['devUID'])
    
  })

  for( let i = 0; i < appStore.transformer_location_data.length; i++){
    if(!transformer_devUIDs.includes(appStore.transformer_location_data[i]['devUID'])){
      let transformer = {
        devUID: appStore.transformer_location_data[i]['devUID'],
        data: {
          output_current: 0,
          output_voltage: 0,
          output_power: 0,
        },
        location : {
          position: [appStore.transformer_location_data[i]['latitude'], appStore.transformer_location_data[i]['longitude']],
          operational: false
        }
      }

      transformers_data.push(transformer)
    }
  }
  
  console.log(transformers_data)
  transformers.value = transformers_data
  console.log("Transformers", transformers.value)
}


const intervalID = ref(null)

watch(() => appStore.transformer_data, (newVal, oldVal) => {
  updateLatestValues(newVal)
})



//lifecycle hooks
onMounted(() => {
    if(appStore.transformer_data == null){
        get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)

        intervalID.value = setInterval(()=>{
          get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)
        }, 300000)
    } else {
        updateLatestValues(appStore.transformer_data)
        intervalID.value = setInterval(()=>{
          get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)
        }, 300000)
    }
})

onUnmounted(() => {
    clearInterval(intervalID.value)
})

</script>
