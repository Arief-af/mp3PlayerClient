<script setup>
import { ref, onMounted } from "vue";
import { useQuasar } from "quasar";
import { useIPStore } from "stores/ip";
const transcript = ref("");
const isRecording = ref(false);
const Recognition = window.SpeechRecognition || window.webkitSpeechRecognition;
const sr = new Recognition();
import axios from "axios";
const store = useIPStore();
const $q = useQuasar();
const changeIP = () => {
  $q.dialog({
    title: "Setting IP",
    message: "Masukan IP Perangkat Mood Music Player  ",
    prompt: {
      model: "",
      type: "text", // optional
    },
    cancel: true,
    persistent: true,
  }).onOk((data) => {
    store.changeIP(data);
  });
};
onMounted(() => {
  sr.lang = "id-ID";
  sr.continuous = true;
  sr.interimResults = true;
  sr.onstart = () => {
    transcript.value = "";
    console.log("SR Started");
    console.log(isRecording);
    isRecording.value = true;
  };
  sr.onend = () => {
    console.log("SR Stopped");
    isRecording.value = false;
  };
  sr.onresult = (evt) => {
    for (let i = 0; i < evt.results.length; i++) {
      const result = evt.results[i];
    }
    const t = Array.from(evt.results)
      .map((result) => result[0])
      .map((result) => result.transcript)
      .join("");

    transcript.value = t;
  };
});

const onOff = () => {
  axios.get(`http://${store.ip}/stop`);
};

const ToggleMic = () => {
  if (isRecording.value) {
    sr.stop();
  } else {
    sr.start();
  }
};

const randomHappy = () => Math.floor(Math.random() * 3) + 1;
const randomSad = () => Math.floor(Math.random() * 3) + 4;
const randomBosan = () => Math.floor(Math.random() * 9) + 1;
const randomBelajar = () => Math.floor(Math.random() * 3) + 7;

const sendApi = (music) => {
  var formData = new FormData();
  formData.append("plain", music);
  axios
    .post(`http://${store.ip}/getMood`, formData)
    .then((res) => {
      console.log(res);
    })
    .catch((err) => {
      console.log(err);
    });
};
const onSend = () => {
  if (
    transcript.value == "aku lagi sedih" ||
    transcript.value == "Aku lagi sedih"
  ) {
    console.log("masuk");
    sendApi(randomSad());
  } else if (transcript.value == "Aku lagi sedih, naikin mood aku dong") {
    sendApi(randomHappy());
  } else if (transcript.value == "hari yang menyenangkan") {
    sendApi(randomHappy());
  } else if (
    transcript.value == "bosan banget" ||
    transcript.value == "bosan" ||
    transcript.value == "bosen banget"
  ) {
    sendApi(randomBosan());
  } else if (transcript.value == "saatnya belajar") {
    sendApi(randomBelajar());
  }
};
</script>
<template>
  <div class="wrapping">
    <div class="config">
      <q-btn class="bg-white text-dark" icon="settings" @click="changeIP" /> IP
      : {{ store.ip }}
    </div>
    <div class="q-pa-sm content">
      <!-- {{ isRecording }} -->
      <div class="circle" @click="ToggleMic">
        <q-icon name="mic" />
      </div>
      <div class="text-center text-white q-pa-md" v-if="isRecording">
        Listening..
      </div>

      <div
        class="transcript q-pa-md text-center text-white"
        v-text="transcript"
      ></div>
      <center></center>
      <!-- {{ transcript }} -->
      <!-- {{ response }} -->
    </div>
  </div>

  <div class="footer">
    <q-btn
      color="dark"
      class="q-pa-md"
      rounded
      icon="home"
      to="/"
      label="home"
    />
    <q-btn
      color="positive"
      class="q-ml-sm"
      rounded
      label="send"
      icon="send"
      @click="onSend"
    />
    <q-btn
      color="negative"
      class="q-ml-sm"
      rounded
      icon="power_off"
      @click="onOff"
    />
  </div>
</template>

<style>
body {
  background: #1d1d1d;
}

.footer {
  position: fixed;
  bottom: 0px;
  left: 0px;
  width: 100%;
  padding: 20px;
  display: flex;
  justify-content: center;
  background: #2c2c2c;
  border-radius: 37px 37px 0px 0px;
}

.content {
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
}

.circle {
  display: flex;
  justify-content: center;
  align-items: center;
  /* border: 2px solid #1d1d1d; */
  color: white;
  border: 9px solid #ffffff;
  width: 212px;
  height: 212px;
  border-radius: 1000px;
  font-size: 64px;
  transition: all 0.5s;
  cursor: pointer;
}

.circle:hover {
  background-color: #454545;
}

.config {
  color: white;
  padding: 30px;
  position: fixed !important;
  top: 0px !important;
  width: 100%;
  padding: 20px;
  display: flex;
  justify-content: center;
  align-items: center;
  gap: 10px;
  background: #2c2c2c;
  border-radius: 0px 0px 37px 37px;
}
</style>
