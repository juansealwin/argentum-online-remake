#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include "texture.h"
#include "character.h"
#include "npc.h"
#include "human.h"
#include "elf.h"
#include "gnome.h"
#include "dwarf.h"

#define MAP_SIZE 3200


class Map {
 private:
  Texture background_texture;
  SDL_Renderer* renderer;
  //La porción del mapa que queremos renderizar
  SDL_Rect map_piece;
  //La parte de la ventana que es renderizable
  SDL_Rect viewport;
  int screen_width;
  int screen_height;
  //std::vector<Character*> characters;
  std::map<int, Character> characters;

 public:
  Map(int, SDL_Renderer*, int, int);
  ~Map();
  void render();
  void updateMap(int, int);
  void updateCharacter(int, move_t);
  void changeMap(int);
  void loadCharacter(character_t, SDL_Renderer*, int, int , int);
  void renderCharacters();
  void cleanCharactersVector();
};

#endif