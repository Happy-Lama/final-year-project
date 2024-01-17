<template>
  <v-navigation-drawer class="bg-red" theme="light" permanent>
    <v-list color="transparent">
      <v-list-item prepend-icon="mdi-map" @click="changeView('Home')" :class="active === 'Home' ? 'activeRoute' : ''">Map</v-list-item>
      <v-list-item prepend-icon="mdi-chart-bar" @click="changeView('Statistics')" :class="active === 'Statistics' ? 'activeRoute' : ''">Statistics</v-list-item>
      <v-list-item prepend-icon="mdi-list-box-outline" @click="changeView('Register')" :class="active === 'Register' ? 'activeRoute' : ''">Register</v-list-item>
      <v-list-item prepend-icon="mdi-bell" @click="changeView('Notifications')" :class="active === 'Notifications' ? 'activeRoute' : ''">Notifications</v-list-item>
    </v-list>
    <template v-slot:append>
      <div class="pa-2">
        <v-btn block @click="logout_fn()">
          Logout
        </v-btn>
      </div>
    </template>
  </v-navigation-drawer>
</template>

<script setup>

import router from '@/router';
// import { route } from 'express/lib/application';
import { onMounted } from 'vue';
import { ref } from 'vue';
import { useAppStore } from '@/store/app';
import { watch } from 'vue';
import { logout } from '@/httpservice';
const appStore = useAppStore()
const active = ref('Home')

const changeView = (routeName) => {
  active.value = routeName
  router.push({name: routeName })
}

const logout_fn = () => {
  logout('http://localhost:8000/dashboard/logout/', appStore);
  appStore.logged_in = false  
}

//lifecycle hooks
onMounted(() => {
  let currentURL = window.location.href;
  let routes = router.getRoutes();
  for(let i = 0; i < routes.length; i++){
    if(currentURL.endsWith(routes[i].path) && routes[i].name !== null){
      active.value = routes[i].name
      break;
    }
  }

})
</script>

<style scoped>

.activeRoute{
  background-color: rgba(212, 0, 0, 0.629);
}

</style>
