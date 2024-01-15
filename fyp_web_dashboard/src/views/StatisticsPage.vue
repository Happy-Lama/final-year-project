<template>

<v-container>
    <v-card class="mb-8" >
        <v-row align="center" justify="center" style="max-height: 100vh;">
            <v-col>
                <CircularChartComponent :chart-data="circhartData"/>
            </v-col>

            <v-divider vertical style="height: 90vh;" class="mt-5" thickness="2"></v-divider>

            <v-col style="height: 100vh;" justify="center" align="center">
                <v-card align="center" style="height: 100vh;" justify="center" variant="flat">
                    <v-card-title>
                        Summary of Statistics
                    </v-card-title>
                    <v-row style="height: 95%;" align="center" justify="center">
                        <v-col cols="6">
                            <v-card variant="flat">
                                <v-card-title class="text-h4">
                                    {{ average_power.toFixed(4) }}
                                </v-card-title>
                                <v-card-text>
                                    Average Power (kW)
                                </v-card-text>
                            </v-card>
                        </v-col>
                        <v-col cols="6">
                            <v-card variant="flat">
                                <v-card-title class="text-h4">
                                    {{ average_voltage }}    
                                </v-card-title>
                                <v-card-text>
                                    Average Voltage (V)
                                </v-card-text>
                                
                            </v-card>
                        </v-col>
                        <v-col cols="6" align-self="start">
                            <v-card variant="flat">
                                <v-card-title class="text-h4">
                                    {{ average_current }}
                                </v-card-title>
                                <v-card-text>
                                    Average Current (A)
                                </v-card-text>
                            </v-card>
                        </v-col>
                        <v-col cols="6" align-self="start">
                            <v-card variant="flat" >
                                <v-card-title class="text-h4">
                                    {{ average_frequency }}
                                </v-card-title>
                                <v-card-text>
                                    Average Frequency (Hz)
                                </v-card-text>
                            </v-card>
                        </v-col>
                    </v-row>
                </v-card>
            </v-col>
        </v-row>
    </v-card>
    
    <v-row>

        <!-- Average Power Chart -->
        <v-col cols="6">
            <ChartComponent :chart-data="powerChartData" chart-title="Average Power" data-type="power"/>
        </v-col>

        <!-- Average Voltage Chart -->
        <v-col cols="6">
            <ChartComponent :chart-data="voltageChartData" chart-title="Average Voltage" data-type="voltage"/>
        </v-col>

        <!-- Average Reactive Power Chart -->
        <v-col cols="6">
            <ChartComponent :chart-data="reactivePowerChartData" chart-title="Average Reactive Power" data-type="reactive_power"/>
        </v-col>

        <!-- Average Current Chart -->
        <v-col cols="6">
            <ChartComponent :chart-data="currentChartData" chart-title="Average Current" data-type="current"/>
        </v-col>

        <!-- Average Frequency Chart  -->
        <v-col cols="6">
            <ChartComponent :chart-data="frequencyChartData" chart-title="Average Frequency" data-type="frequency"/>
        </v-col>

    </v-row>
</v-container>

</template>

<script setup>

import { ref, watch } from 'vue';
import ChartComponent from '@/components/ChartComponent.vue';
import CircularChartComponent from '@/components/CircularChartComponent.vue';
import { useAppStore } from '@/store/app';
import { onMounted } from 'vue';
import { get_average_values, get_latest_transformer_data } from '@/httpservice';
import { onUnmounted } from 'vue';

const appStore = useAppStore();
const average_power = ref(0.0);
const average_voltage = ref(0.0);
const average_current = ref(0.0);
const average_frequency = ref(0.0);

const circhartData = ref({
  online: 0,
  offline: 0,
});

const powerChartData = ref({
    label: 'Power',
    data: {
        x: [],
        y: []
    }
});
const reactivePowerChartData = ref({
    label: 'Reactive Power',
    data: {
        x: [],
        y: []
    }
});
const voltageChartData = ref({
    label: 'Voltage',
    data: {
        x: [],
        y: []
    }
})
const currentChartData = ref({
    label: 'Current',
    data: {
        x: [],
        y: []
    }
})
const frequencyChartData = ref({
    label: 'Frequency',
    data: {
        x: [],
        y: []
    }
})

function updateValues(newVal){
    average_current.value = newVal['average_output_current']
    average_voltage.value = newVal['average_output_voltage']
    average_power.value = newVal['average_output_power']/1000
    average_frequency.value = newVal['average_output_frequency']
    console.log(average_current.value)
    // average_current.value = 100

    circhartData.value = {
        online: 0,
        offline: 0,
    }

    appStore.transformer_location_data.forEach((location) => {
        // console.log(location)
        

        if(location['operational']){
            circhartData.value = { online: ++circhartData.value.online , offline: circhartData.value.offline }
        } else {
            circhartData.value = { online: circhartData.value.online , offline: ++circhartData.value.offline }
        }
    })

    console.log(circhartData.value)
    let timestamps = []
    let powerdata = []
    let currentdata = []
    let voltagedata = []
    let reactivepowerdata = []
    let frequencydata = []
    if(appStore.moving_average_values){
        appStore.moving_average_values.forEach((data) => {
            timestamps.push(data['timestamp'])
            powerdata.push(data['average_values']['output_power__avg']/1000)
            currentdata.push(data['average_values']['output_current__avg'])
            voltagedata.push(data['average_values']['output_voltage__avg'])
            reactivepowerdata.push(data['average_values']['output_reactive_power__avg']/1000)
            frequencydata.push(data['average_values']['output_frequency__avg'])
        })
    
        powerChartData.value = {
            label: 'Power',
            data: {
                x: timestamps,
                y: powerdata
            }
        }
        

        currentChartData.value = {
            label: 'Current',
            data: {
                x: timestamps,
                y: currentdata
            }
        }
        

        voltageChartData.value ={
            label: 'Voltage',
            data: {
                x: timestamps,
                y: voltagedata
            }
        }
        
        
        reactivePowerChartData.value = {
            label: 'Reactive Power',
            data: {
                x: timestamps,
                y: reactivepowerdata
            }
        }
        

        frequencyChartData.value = {
            label: 'Frequency',
            data: {
                x: timestamps,
                y: frequencydata
            }
        }
    }
}

const intervalID = ref(null)

watch(() => appStore.average_values, (newVal, oldVal) => {
    updateValues(newVal)
})

onMounted(() => {
    if(appStore.average_values == null){
        get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)
        get_average_values('http://localhost:8000/data/transformers/average_values/', appStore)

        intervalID.value = setInterval(()=>{
            get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)
            get_average_values('http://localhost:8000/data/transformers/average_values/', appStore)
        }, 300000)
    } else {
        updateValues(appStore.average_values)
        intervalID.value = setInterval(()=>{
            get_latest_transformer_data('http://localhost:8000/data/transformers/latest/', appStore)
            get_average_values('http://localhost:8000/data/transformers/average_values/', appStore)
        }, 300000)
    }
})

onUnmounted(() => {
    clearInterval(intervalID.value)
})

</script>