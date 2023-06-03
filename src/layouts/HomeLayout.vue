<template>
  <div>
    <div class="content__home__wrapper text-white">
      <div class="content__home bg-dark">
            <div class="letters">Mood Music Player</div>
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

.letters{
  font-size: 20px;
}

.content__home__wrapper {
  position: absolute;
  top: 40%;
  left: 50%;
  transform: translate(-50%, -50%);
}

</style>
