<template>
  <div>
    <div class="content__home__wrapper text-white">
      <div class="content__home bg-dark">
        <img class="hero__mascot" src="hero1.png" alt="" />
        <h1 class="ml9">
          <span class="text-wrapper">
            <span class="letters">Mood MP3 Player</span>
          </span>
        </h1>
      </div>
    </div>
    <div class="footer">
      <q-btn color="dark" class="q-pa-md" rounded icon="home" label="home" />
      <q-btn
        color="positive"
        class="q-ml-sm"
        rounded
        label="GO!"
        icon="music_note"
        to="/play"
      />
    </div>
  </div>
</template>

<style>
.content__home {
  position: relative;
  width: 300px;
  height: 200px;
  max-width: 300px;
  border-radius: 30px;
  margin: 0 auto;
  display: flex;
  justify-content: center;
  align-items: center;
  border-radius: 30px !important;
}

.hero__mascot {
  position: absolute !important;
  top: -49px !important;
  right: -40px !important;
}

.content__home__wrapper {
  position: absolute;
  top: 40%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.ml9 {
  font-weight: 200;
  font-size: 4em;
}

.ml9 .text-wrapper {
  position: relative;
  display: inline-block;
  overflow: hidden;
}

.ml9 .letter {
  transform-origin: 50% 100%;
  display: inline-block;
  line-height: 1em;
  font-size: 24px;
}
</style>

<script setup>
import anime from 'animejs/lib/anime.es.js';    
import { onMounted } from "vue";

// Wrap every letter in a span
onMounted(() => {
  speechSynthesis.cancel();
  let textWrapper = document.querySelector(".ml9 .letters");
  textWrapper.innerHTML = textWrapper.textContent.replace(
    /\S/g,
    "<span class='letter'>$&</span>"
  );

  anime
    .timeline({ loop: true })
    .add({
      targets: ".ml9 .letter",
      scale: [0, 1],
      duration: 1500,
      elasticity: 600,
      delay: (el, i) => 45 * (i + 1),
    })
    .add({
      targets: ".ml9",
      opacity: 0,
      duration: 1000,
      easing: "easeOutExpo",
      delay: 1000,
    });
});
</script>