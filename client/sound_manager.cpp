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
}
