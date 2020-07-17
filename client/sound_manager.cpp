#include "sound_manager.h"

SoundManager::SoundManager() { charge_sound_music(); }

SoundManager::~SoundManager() {}

void SoundManager::charge_sound_music() {
  /************** MUSICAS DE FONDO *****************/
  music[BG_MUSIC_1].set_music("musica_lobby.mp3");

  /************** SONIDOS AL CAMINAR *****************/
  sound_effects[WALK_PC].set_sound("caminar.wav");
  sound_effects[WALK_SPIDER].set_sound("caminar_araña.wav");
  sound_effects[WALK_SKELETON].set_sound("caminar_araña.wav");
  sound_effects[WALK_GOBLIN].set_sound("caminar_goblin.wav");
  sound_effects[WALK_ZOMBIE].set_sound("caminar_zombie.wav");
  sound_effects[CAST_BLEEDING].set_sound("sangrado.mp3");
  sound_effects[CAST_MAGIC_ARROW].set_sound("flecha_magica.wav");
  sound_effects[CAST_HEAL].set_sound("curar.wav");
  sound_effects[CAST_ELECTRIC_SHOCK].set_sound("descarga_electrica.wav");
  sound_effects[CAST_EXPLOSION].set_sound("explosion.wav");
  //sound_effects[CAST_REVIVE].set_sound("revivir.wav");
  sound_effects[CAST_MEDITATION].set_sound("meditar.wav");
  sound_effects[DEAD_PC].set_sound("muerto.wav");
}

void SoundManager::play_music(sound_t id) {
  music[id].play_music();
  music[id].decrease_music_volume(90);
}

void SoundManager::play_sound_effects(std::vector<sound_t>& current_sounds) {
  while (!current_sounds.empty()) {
    sound_effects[current_sounds.back()].play_sound(0);
    current_sounds.pop_back();
  }
}