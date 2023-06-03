import { defineStore } from 'pinia';

export const useIPStore = defineStore('useIPStore', {
  state: () => ({
    ip: '192.168.124.7',
  }),
  actions: {
    changeIP(IP) {
      this.ip = IP;
    },
  },
  persist: true
});
