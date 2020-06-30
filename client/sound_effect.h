#ifndef SOUND_EFFECT_H
#define SOUND_EFFECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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
  // Constructor por defecto
  SoundEffect();

  // Destructor, libera el Mix_Chunk
  ~SoundEffect();

  // Setea los archivos de sonidos
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

  // Aumenta el volumen de la musica
  void increase_music_volume(int inc = 10);

  // Disminuye el volumen de la musica
  void decrease_music_volume(int dec = 10);

  // Para el sonido
  void stop_sound();

  // Checkea si esta playing
  bool is_playing();
};

#endif