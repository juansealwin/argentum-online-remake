#include "sound_effect.h"
#include <limits.h>

int CHANNEL_COUNTER = 1;

SoundEffect::SoundEffect() {
  sound = nullptr;
  music = nullptr;
  playing_music = false;
  playing_sound = false;
  if (CHANNEL_COUNTER == INT_MAX) 
    CHANNEL_COUNTER = 1;
  
  channel = CHANNEL_COUNTER++;
  Mix_AllocateChannels(Mix_AllocateChannels(-1) + 1);
}

SoundEffect::~SoundEffect() {
  free_sound();
  free_music();
}

void SoundEffect::free_sound() {
  playing_sound = false;
  Mix_HaltChannel(channel);
  if (sound) {
    Mix_FreeChunk(sound);
    sound = NULL;
  }
}

void SoundEffect::free_music() {
  if (music) {
    Mix_HaltChannel(channel);
    Mix_FreeMusic(music);
    music = NULL;
  }
}

void SoundEffect::set_sound(std::string path) {
  free_sound();
  sound = Mix_LoadWAV(path.c_str());
  if (!sound) 
    throw SdlException(MSG_ERROR_LOAD_SOUND, Mix_GetError());
}

void SoundEffect::set_music(std::string path) {
  free_music();
  music = Mix_LoadMUS(path.c_str());
  if (!music) 
    throw SdlException(MSG_ERROR_LOAD_MUSIC, Mix_GetError());
}

void SoundEffect::play_sound(int loops) {
  if (Mix_Playing(channel) == 0) {
    playing_sound = false;
  }

  if (!playing_sound && sound) {
    Mix_PlayChannel(channel, sound, loops);
    playing_sound = true;
  }
}

void SoundEffect::stop_sound() { Mix_HaltChannel(channel); }

void SoundEffect::play_music(int loops) {
  if (!Mix_PlayingMusic()) {
    playing_music = false;
    if (music) {
      Mix_PlayMusic(music, loops);
      playing_music = true;
    }
  }

  if (Mix_PausedMusic())
    Mix_ResumeMusic();
}

void SoundEffect::increase_music_volume(int inc) {
  music_volume = Mix_VolumeMusic(-1);
  music_volume + inc > MIX_MAX_VOLUME ? Mix_VolumeMusic(MIX_MAX_VOLUME)
                                      : Mix_VolumeMusic(music_volume + inc);
}

void SoundEffect::decrease_music_volume(int dec) {
  music_volume = Mix_VolumeMusic(-1);
  music_volume - dec < 0 ? Mix_VolumeMusic(0)
                         : Mix_VolumeMusic(music_volume - dec);
}

bool SoundEffect::is_playing() { return Mix_Playing(channel) != 0; }