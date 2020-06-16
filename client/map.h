#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "texture.h"
#include "character.h"
#include "npc.h"
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
  std::vector<Character*> characters;

 public:
  Map(int, SDL_Renderer*, int, int);
  ~Map();
  void render();
  void update(int, int);
  void changeMap(int);
  void loadCharacter(SDL_Renderer*, int, int , int);
  void renderCharacters();
  void cleanCharactersVector();
};

#endif