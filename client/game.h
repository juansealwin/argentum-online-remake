#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <vector>

#include "character.h"
#include "dwarf.h"
#include "elf.h"
#include "event.h"
#include "exception_messages.h"
#include "gnome.h"
#include "human.h"
#include "map.h"
#include "npc.h"
#include "sdl_exception.h"
#include "texture.h"
#include "blocking_queue.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"

class Game {
 private:
  int id_player;
  BlockingQueue& events_queue;
  bool is_running;
  /*std::vector<Texture*> textures;
  PlayableCharacter* player;
  Map* current_map;
  int screen_width = 800;
  int screen_height = 600;*/

 public:
  Game(int, BlockingQueue&);
  ~Game();
  void window_init();
  void fill(int, int, int, int);
  bool is_up();
  void new_player(PlayableCharacter*);
  void event_handler();
  void update();
  void render();
  SDL_Renderer* get_renderer();
  Texture* get_texture(int);
  void delete_textures();
};

#endif
