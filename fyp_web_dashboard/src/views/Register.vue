<template>
    <v-container align="center" class="pt-15">
        <v-row justify="center">
            <v-card class="pa-5" style="min-width: 25rem; max-width: 35rem; background-color: white;" align="center">
                <v-card-title>
                    Transformer Registration Form
                </v-card-title>
                <v-card-item>
                    <v-form class="pt-5">
                        <v-text-field label="DevUID" variant="outlined" v-model="devUID"></v-text-field>
                        <v-text-field label="Nominal Power Rating" variant="outlined" v-model="nominal_power_rating"></v-text-field>
                        <v-card variant="flat" align="left">
                            <v-card-title class="mb-2">Position</v-card-title>    
                            <v-row>
                                <v-col>
                                    <v-text-field label="Latitude" variant="outlined" v-model="lat"></v-text-field>
                                </v-col>
                                <v-col>
                                    <v-text-field label="Longitude" variant="outlined" v-model="lng"></v-text-field>
                                </v-col>
                            </v-row>
                        </v-card>
                    </v-form>
                </v-card-item>
                <v-btn @click="submit()">
                    Submit
                </v-btn>
            </v-card>
        </v-row>
    </v-container>
</template>


<script setup>
import { ref, onMounted } from 'vue';
import { register } from '@/httpservice';
import { useAppStore } from '@/store/app';

const devUID = ref(null)
const lat = ref(null)
const lng = ref(null)
const nominal_power_rating = ref(null)
const appStore = useAppStore()

const submit = () => {
    console.log(devUID.value);
    console.log(lat.value);
    console.log(lng.value);

    if(devUID.value && lat.value && lng.value && nominal_power_rating.value){
        let formData = new FormData();
        formData.append('devUID', devUID.value);
        formData.append('latitude', lat.value);
        formData.append('longitude', lng.value)
        formData.append('nominal_power_rating', nominal_power_rating.value)
        register('http://localhost:8000/data/transformers/register/', formData, appStore);
    } else {
        alert("Fill in the devUID, Latitude and Longitude")
    }
}

//lifecycle hooks
onMounted(() => {
    if(window.navigator.geolocation && !lat.value && !lng.value){
        window.navigator.geolocation.getCurrentPosition((position) => {
            lat.value = position.coords.latitude;
            lng.value = position.coords.longitude;

            console.log(`Latitude: ${lat.value}, Longitude: ${lng.value}`);
        })
    }
});

</script>