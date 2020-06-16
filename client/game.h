#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <vector>

#include "map.h"
#include "dwarf.h"
#include "elf.h"
#include "exception_messages.h"
#include "gnome.h"
#include "human.h"
#include "character.h"
#include "sdl_exception.h"
#include "texture.h"
#include "npc.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"

class Game {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector<Texture*> textures;
  PlayableCharacter* player;
  Map* current_map;
  bool is_running;
  int screen_width = 800;
  int screen_height = 600;

 public:
  Game(int, int);
  ~Game();
  void windowInit();
  void fill(int, int, int, int);
  bool isRunning();
  void newPlayer(PlayableCharacter*);
  void eventHandler();
  void update();
  void render();
  SDL_Renderer* getRenderer();
  Texture* getTexture(int);
  void deleteTextures();
};

#endif