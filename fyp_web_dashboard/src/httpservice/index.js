import axios from 'axios';
// import { useAppStore } from '@/store/app';
import router from '@/router';


// const appStore = useAppStore();

function login(url, formData, store){
    //send login request
    axios.post(url, formData, {
        headers: {
            'X-CSRFtoken': store.csrfToken,
            "Content-Type": "multipart/form-data",
        },
        withCredentials: true,
    }).then((response) => {
        console.log("Data", response.data)
        store.logged_in = true;
        router.push({ name: 'Home' })
    }).catch((error) => {
        console.error(error);
        alert("Wrong password or email")
    });
}

function get_csrf_token(url, store){
    axios.get(url)
    .then((response) => {
        console.log(response.data)
        store.csrfToken = response.data['csrfToken']
        console.log("Stored Token", store.csrfToken)
        document.cookie = `csrftoken=${store.csrfToken}; path=/`
    })
    .catch((error) => {
        console.error(error);
    })
}

function register(url, formData, store){
    axios.post(url, formData, {
        headers: {
            'X-CSRFtoken': store.csrfToken,
            "Content-Type": "multipart/form-data",
        },
        withCredentials: true,
    }).then((response) => {
        console.log("Data", response.data)
    }).catch((error) => {
        console.error(error);
        alert("Failed to register Transformer")
    });    
}

function get_transformer_data(url, store){
    axios.get(url)
    .then((response) => {
        console.log(response.data)
        store.transformer_data = response.data['transformer_data']
        store.transformer_location_data = response.data['transformer_location_data']
        store.average_values = response.data['average_values']
        store.moving_average_values = response.data['moving_average_values']
        console.log("Stored Transformer Data", store.transformer_data)
        console.log("Stored Transformer Location Data", store.transformer_location_data)
        console.log("Stored Average Values", store.average_values)
        console.log("Stored Moving Average Values", store.moving_average_values)
    })
    .catch((error) => {
        console.error(error);
    })    
}
export { login, get_csrf_token, register, get_transformer_data }
