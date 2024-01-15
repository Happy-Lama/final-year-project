<template>
    <div id="map" style="height: 100vh;">
        <!-- {{ transformers }} -->
    </div>

</template>

<script setup>

import L from 'leaflet';
import 'leaflet/dist/leaflet.css';
import { watch } from 'vue';
import { ref } from 'vue';
import { onMounted } from 'vue';

//props
const props = defineProps(['transformers']);

//data
const transformers = ref(props.transformers);
const map = ref(null)
const mapmarkers = ref([]);
const transformer_locations = ref(null)


//custom icon markers

const operationalIcon = L.icon({
    iconUrl: '/operationalIcon.png',
    iconSize:     [32, 32], // size of the icon
    iconAnchor:   [16, 32], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -32] // point from which the popup should open relative to the iconAnchor
});

const faultyIcon = L.icon({
    iconUrl: '/faultyIcon.png',
    iconSize:     [32, 32], // size of the icon
    iconAnchor:   [16, 32], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -32] // point from which the popup should open relative to the iconAnchor
});



function updateMarkers(){
    console.log('Updating map markers')
    //marker for each transformer received
    let locations = []
    transformers.value.forEach((transformer) => {
        
        let mapmarker = L.marker(transformer.location.position, {
            icon: transformer.location.operational ? operationalIcon : faultyIcon
        });
        
        locations.push(transformer.location.position)

        mapmarker.bindTooltip(`Current: ${transformer.data.output_current.toFixed(2)}<br/>Voltage: ${transformer.data.output_voltage.toFixed(2)}<br/>Power: ${transformer.data.output_power.toFixed(2)}<br/>Status: ${transformer.location.operational ? 'Operational': 'Faulty'}`);

        mapmarker.on('mouseover', () => {
            this.openTooltip();
        });

        mapmarker.on('mouseout', () => {
            this.closeTooltip();
        });

        mapmarkers.value.push(mapmarker)
    });

    if(locations){
        let bounds = L.latLngBounds(locations)
        if(map.value){
            map.value.fitBounds(bounds)
        }
    }
}


watch(() => props.transformers, (newVal, oldVal) => {
    console.log('Transformers have changed')
    transformers.value = newVal
    updateMarkers();
    mapmarkers.value.forEach((mapmarker)=>{
        mapmarker.addTo(map.value);
        console.log('Added to map')
    });
}) 

onMounted(() => {
    map.value = L.map('map').setView([0.34759640, 32.58251970], 12);
    L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
        maxZoom: 19,
        attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
    }).addTo(map.value);
    // transformers.value = props.transformers;

    mapmarkers.value.forEach((mapmarker)=>{
        mapmarker.addTo(map.value);
        console.log('Added to map')
    });
});


</script>