<template>
  <router-view />
</template>

<script setup>
import { watch, ref } from 'vue';
import { useAppStore } from './store/app';
import router from './router';
import { onMounted } from 'vue';
import { get_notifications } from './httpservice';
import { onUnmounted } from 'vue';


const appStore = useAppStore();
let intervalID = ref(null)

watch(() => appStore.logged_in, (newVal, oldVal) => {
  // console.log("appStore.logged_in has changed", newVal, oldVal)
  if(newVal === false){
    router.push({ name: 'Login' });
  }
})

onMounted(()=>{
  get_notifications('http://localhost:8000/dashboard/notifications/latest/', appStore)

  intervalID.value = setInterval(() => {
    get_notifications('http://localhost:8000/dashboard/notifications/latest/', appStore)
    console.log("New Notifications")
  }, 30000)

})

onUnmounted(() => {
  clearInterval(intervalID.value)
})
</script>
