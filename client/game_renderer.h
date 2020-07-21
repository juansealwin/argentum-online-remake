#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

#include "events_queue.h"
#include "game.h"
#include "playable_character.h"
#include "protected_map.h"
#include "sdl_exception.h"
#include "sound_effect.h"
#include "spell.h"
#include "texture.h"
#include "texture_manager.h"
#include "thread.h"
#include "text_box.h"
#include "sound_manager.h"

// 40 FPS
#define FRAME_DELAY 1000/10

class GameRenderer : public Thread {
 private:
  SDL_Renderer* renderer;
  bool is_running;
  int screen_width;
  int screen_height;
  UIStatus ui;
  ProtectedMap& protected_map;
  EventsQueue& events_queue;
  std::vector<sound_t> current_sounds;

 public:
  GameRenderer(SDL_Renderer*, int, int, ProtectedMap&, EventsQueue&);
  ~GameRenderer();
  void window_init();
  void run();
};

#endif