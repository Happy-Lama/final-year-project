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
const transformers = ref(props.transformers ? props.transformers : []);
const map = ref(null)
const mapmarkers = ref([]);



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
    //marker for each transformer received
    transformers.value.forEach((transformer) => {
        
        let mapmarker = L.marker(transformer.location.position, {
            icon: transformer.location.operational ? operationalIcon : faultyIcon
        });

        mapmarker.bindTooltip(`Current: ${transformer.data.output_current}<br/>Voltage: ${transformer.data.output_voltage}<br/>Power: ${transformer.data.output_power}<br/>Status: ${transformer.location.operational ? 'Operational': 'Faulty'}`);

        mapmarker.on('mouseover', () => {
            this.openTooltip();
        });

        mapmarker.on('mouseout', () => {
            this.closeTooltip();
        });

        mapmarkers.value.push(mapmarker)
    });
}


watch(() => props.transformers, (newVal, oldVal) => {
    transformers.value = newVal
    updateMarkers();
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
    });
});


</script>