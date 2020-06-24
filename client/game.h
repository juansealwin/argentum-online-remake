#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>

#include "character.h"
#include "npc.h"
#include "playable_character.h"
#include "texture.h"
#include "texture_manager.h"
#include "types.h"

#define MAP_SIZE 3200

class Game {
 private:
  int id_hero;
  id_texture_t type_map;
  SDL_Renderer* renderer;
  // La porción del Gamea que queremos renderizar
  SDL_Rect map_piece;
  // La parte de la ventana que es renderizable
  SDL_Rect viewport;
  int screen_width;
  int screen_height;
  std::map<int, Character> characters;

 public:
  Game(int, id_texture_t, SDL_Renderer*, int, int);
  Game(const Game&);
  Game& operator=(const Game&);
  ~Game();
  void render();
  void update_map(int, int);
  void update_character(int, int, int);
  void change_map(int);
  void load_character(character_t, int, int, int);
  void render_characters();
  void clean_character(int i);
};

#endif