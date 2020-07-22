#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <limits.h>

#include <string>

#include "sdl_exception.h"

extern int CHANNEL_COUNTER;

class SoundEffect {
 private:
  Mix_Chunk* sound;
  Mix_Music* music;
  bool playing_sound;
  bool playing_music;
  int channel;
  int music_volume;
  // Libera la memoria del sonido
  void free_sound();
  // Libera la memoria de la musica
  void free_music();
  void channel_finished();

 public:
  SoundEffect();
  ~SoundEffect();
  void set_sound(std::string);
  void set_music(std::string);
  
  // Reproduce el sonido loops+1
  // veces. -1: reproduce eternamente
  // hasta que se lo detenga.
  void play_sound(int loops = -1);

  // Reproduce la musica loops+1
  // veces. -1: reproduce eternamente
  // hasta que se lo detenga.
  void play_music(int loops = -1);
  void increase_music_volume(int inc = 10);
  void decrease_music_volume(int dec = 10);
  void stop_music();
};

#endif