// Utilities
import { defineStore } from 'pinia'
import { computed, ref } from 'vue'

const useAppStore = defineStore('app', ()=>{
  const csrfToken = ref(null)
  const logged_in = ref(null)
  const transformer_data = ref(null)
  const transformer_location_data = ref(null)
  const moving_average_values = ref(null)
  const average_values = ref(null)

  return csrfToken, logged_in, average_values, moving_average_values, transformer_data, transformer_location_data
})


export { useAppStore }