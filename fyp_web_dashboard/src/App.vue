<template>
  <router-view />
</template>

<script setup>
import { watch } from 'vue';
import { useAppStore } from './store/app';
import router from './router';
import { onMounted, ref } from 'vue';
import { onUnmounted } from 'vue';
import { get_transformer_data } from './httpservice';

const appStore = useAppStore();

watch(() => appStore.logged_in, (newVal, oldVal) => {
  // console.log("appStore.logged_in has changed", newVal, oldVal)
  if(newVal === false) router.push({ name: 'Login' });
})

const  intervalID = ref(null)

onMounted(() => {
  intervalID.value = setInterval(() => {
    get_transformer_data('http://localhost:8000/data/transformers/', appStore)
  }, 30000);
})

onUnmounted(() => {
  clearInterval(intervalID.value)
})
</script>
