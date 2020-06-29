#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>

#include <vector>
#include "protected_map.h"
#include "exception_messages.h"
#include "game.h"
#include "playable_character.h"
#include "sdl_exception.h"
#include "texture.h"
#include "thread.h"
#include "texture_manager.h"
#include "events_queue.h"
#define FRAME_DELAY 100/6

class GameRenderer : public Thread {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool is_running;
  int screen_width;
  int screen_height;
  ProtectedMap& protected_map;
  EventsQueue& events_queue;

 public:
  GameRenderer(int, int, ProtectedMap&, EventsQueue&);
  ~GameRenderer();
  void window_init();
  void run();
};

#endif