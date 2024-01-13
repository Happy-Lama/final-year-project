// Composables
import { get_csrf_token } from '@/httpservice'
import { createRouter, createWebHistory } from 'vue-router'
import { useAppStore } from '@/store/app'



const routes = [
  {
    path: '/',
    component: () => import('@/layouts/default/Default.vue'),
    children: [
      {
        path: '',
        name: 'Home',
        // route level code-splitting
        // this generates a separate chunk (Home-[hash].js) for this route
        // which is lazy-loaded when the route is visited.
        component: () => import('@/views/Home.vue'),
      },
      {
        path: 'stats',
        name: 'Statistics',
        component: () => import('@/views/StatisticsPage.vue'),
      },
      {
        path: 'register',
        name: 'Register',
        component: () => import('@/views/Register.vue'),
      },
    ],
    meta: { authRequired: true }
  },
  {
    path: '/login',
    name: 'Login',
    component: () => import('@/views/Login.vue'),
    meta: { authRequired: false }
  }

]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes,
})


router.beforeEach((to, from, next)=>{
  const appStore = useAppStore();
  get_csrf_token('http://localhost:8000/dashboard/get_csrf_token/', appStore)
  next()
})

export default router
