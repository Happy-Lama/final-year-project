<template>
    <v-card>
        <v-card-title>
            {{ chartTitle || "Chart Title" }}
        </v-card-title>
        <Line :data="chartData" :options="chartOptions"></Line>
    </v-card>    
</template>

<script setup>
import {
Chart as ChartJS,
CategoryScale,
LinearScale,
PointElement,
LineElement,
Title,
Tooltip,
Legend
} from 'chart.js'
import { Line } from 'vue-chartjs'
import { ref, watch } from 'vue'

ChartJS.register(
CategoryScale,
LinearScale,
PointElement,
LineElement,
Title,
Tooltip,
Legend
)

const props = defineProps(['chartData', 'chartTitle', 'dataType'])

const chartData = ref({
    labels: [], 
    datasets: [
        {
            label: [], 
            backgroundColor: "#f80000",
            borderColor: "#f80000",
            data: []
        }
    ]
})


watch(() => props.chartData, (newVal, oldVal) => {
    // console.log('Old Value', chartData.value)
    chartData.value = {
        labels: newVal.data.x, 
        datasets: [
            {
                label: newVal.label, 
                backgroundColor: "#f80000",
                borderColor: "#f80000",
                data: newVal.data.y
            }
        ]
    }
    // console.log('New Value', chartData.value)
})

const chartOptions = ref({
    responsive: true,
    maintainAspectRation: true,
    scales: {
        x: {
            title : {
                display: true,
                text: "Time"
            }, 
            ticks : {
                display: false,
            }
        },
        y: {
            title : {
                display: true,
                text: "Y-Axis"
            },
            ticks : {
                callback: function(value, index, ticks) {
                        if (props.dataType === "voltage"){
                            return value + "V";
                        }
                        if(props.dataType === "current"){
                            return value + "A";
                        }
                        if(props.dataType === "power"){
                            return value.toFixed(2) + "kW";
                        }
                        if(props.dataType === "reactive_power"){
                            return value.toFixed(2) + "kVAR";
                        }
                        if(props.dataType === "frequency"){
                            return value + "Hz";
                        }
                        return value;
                    } 
            }
        }
    }
})

</script>
  