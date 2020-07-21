#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <unordered_map>
#include <vector>

#include "sound_effect.h"
#include "types.h"

class SoundManager {
 private:
  sound_t actual_music;
  std::unordered_map<sound_t, SoundEffect> music;
  std::unordered_map<sound_t, SoundEffect> sound_effects;

 public:
  SoundManager();
  ~SoundManager();
  void charge_sound_music();
  void play_music();
  void stop_music();
  void increase_music_volume(int = 10);
  void decrease_music_volume(int = 10);
  void play_sound_effects(std::vector<sound_t>&);
};

#endif