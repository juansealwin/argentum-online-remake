#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <vector>

#include "character.h"
#include "commands_blocking_queue.h"
#include "dwarf.h"
#include "elf.h"
#include "exception_messages.h"
#include "gnome.h"
#include "human.h"
#include "map.h"
#include "move_command_dto.h"
#include "npc.h"
#include "sdl_exception.h"
#include "texture.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"

class Game {
 private:
  const int player_id;
  CommandsBlockingQueue& commands_queue;
  bool is_running = true;
  /*std::vector<Texture*> textures;
  PlayableCharacter* player;
  Map* current_map;
  int screen_width = 800;
  int screen_height = 600;*/

 public:
  Game(const int player_id, CommandsBlockingQueue& commands_queue);
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
