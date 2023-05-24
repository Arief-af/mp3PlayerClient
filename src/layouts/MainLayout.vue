<script setup>
import { ref, onMounted } from "vue";
const transcript = ref("");
const isRecording = ref(false);
const Recognition = window.SpeechRecognition || window.webkitSpeechRecognition;
const sr = new Recognition();
import { api } from "boot/axios";
let response = ref("");
onMounted(() => {
  api.get("/").then((res) => {
    console.log(res);
  });
  sr.lang = "id-ID";
  sr.continuous = true;
  sr.interimResults = true;
  sr.onstart = () => {
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
      if (result.isFinal) CheckForCommand(result);
    }
    const t = Array.from(evt.results)
      .map((result) => result[0])
      .map((result) => result.transcript)
      .join("");

    transcript.value = t;
  };
});

const sendApi = (mood) => {
  switch (mood) {
    case "senang":
      console.log("senang");
      break;
    case "sedih":
      let audio = new Audio("/music/1.mp3");
      audio.play();
      // code block
      console.log("sedih");
      break;
    case "bosan":
      // code block
      console.log("bosan");
      break;
    case "belajar":
      console.log("belajar");
      // code block
      break;
    default:
    // code block
  }
};
const CheckForCommand = (result) => {
  const t = result[0].transcript;
  if (t.includes("Aku lagi sedih")) {
    sendApi("sedih");
    sr.stop();
  } else if (t.includes("hari yang menyenangkan")) {
    sendApi("senang");
    sr.stop();
  } else if (
    t.includes("bosan banget") ||
    t.includes("bosan") ||
    t.includes("bosen banget")
  ) {
    sendApi("bosan");
    sr.stop();
  } else if (t.includes("saatnya belajar")) {
    sendApi("belajar");
    sr.stop();
  }
};
const ToggleMic = () => {
  if (isRecording.value) {
    sr.stop();
  } else {
    sr.start();
  }
};

const onSend = () => {
  api
    .post("/", {
      message: "",
    })
    .then((res) => {
      console.log(res);
    })
    .catch((err) => {
      // alert("tunggu 20 detik beb");
      console.log(err);
    });
};
</script>

<template>
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
    <center>
      <q-btn
        class="bg-white q-mx-auto text-dark q-mt-sm text-center"
        icon="send"
        label="send"
        @click="onSend"
      />
    </center>
    <!-- {{ transcript }} -->
    <!-- {{ response }} -->
  </div>
</template>

<style>
body {
  background: #1d1d1d;
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
</style>
