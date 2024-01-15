<template>
  <router-view />
</template>

<script setup>
import { watch } from 'vue';
import { useAppStore } from './store/app';
import router from './router';


const appStore = useAppStore();

watch(() => appStore.logged_in, (newVal, oldVal) => {
  // console.log("appStore.logged_in has changed", newVal, oldVal)
  if(newVal === false) router.push({ name: 'Login' });
})


</script>
