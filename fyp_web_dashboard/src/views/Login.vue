<template>
    <v-container align="center" class="pt-15">
        <v-row justify="center">
            <v-card class="pa-5" style="max-width: 35rem; background-color: white;" align="center">
                <v-card-title>
                    DTMS Web Dashboard Login Page
                </v-card-title>
                <v-card-item>
                    <v-form class="pt-5">
                        <v-text-field label="Email" variant="outlined" type="email" v-model="email"></v-text-field>
                        <v-text-field label="Password" variant="outlined" type="password" v-model="password"></v-text-field>
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
import { get_csrf_token, login } from '@/httpservice'
// import { onMounted } from 'vue';
import { ref } from 'vue'
import { useAppStore } from '@/store/app'

const email = ref(null);
const password = ref(null);
const appStore = useAppStore();

const submit = () => {
    let formData = new FormData();
    if(email.value && password.value){
        formData.append('email', email.value);
        formData.append('password', password.value);
        login('http://localhost:8000/dashboard/login/', formData, appStore);
    } else {
        alert("Fill in the email and password")
    }
}

</script>