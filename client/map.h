#ifndef MAP_H
#define MAP_H

#include <map>
#include <string>
#include <vector>

#include "character.h"
#include "dwarf.h"
#include "elf.h"
#include "gnome.h"
#include "human.h"
#include "npc.h"
#include "texture.h"

#define MAP_SIZE 3200

class Map {
 private:
  int id_hero;
  Texture background_texture;
  SDL_Renderer* renderer;
  // La porción del mapa que queremos renderizar
  SDL_Rect map_piece;
  // La parte de la ventana que es renderizable
  SDL_Rect viewport;
  int screen_width;
  int screen_height;
  std::map<int, Character> characters;

 public:
  Map(int, int, SDL_Renderer*, int, int);
  ~Map();
  void render();
  void update_map(int, int);
  void update_character(int, int, int);
  void change_map(int);
  void load_character(SDL_Renderer*, character_t, int, int, int);
  void render_characters();
  void clean_characters_vector();
};

#endif