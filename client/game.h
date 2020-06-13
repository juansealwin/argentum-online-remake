#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include <vector>

#include "exception_messages.h"
#include "player.h"
#include "sdl_exception.h"
#include "texture.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"
#define PATH_HUMAN_BODY "humano.png"
#define PATH_HUMAN_HEAD "cabeza_humano.png"
#define PATH_ELF_BODY "elfo.png"
#define PATH_ELF_HEAD "cabeza_elfo.png"
#define PATH_DWARF_BODY "enano.png"
#define PATH_DWARF_HEAD "cabeza_enano.png"
#define PATH_GNOME_BODY "gnomo.png"
#define PATH_GNOME_HEAD "cabeza_gnomo.png"

class Game {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector<Texture*> textures;
  Player* player;
  bool is_running;
  int screen_width = 800;
  int screen_height = 600;
  SDL_Rect body_player = {0, 0, 25, 45};
  SDL_Rect head_player = {0, 0, 17, 16};

 public:
  Game(int, int);
  ~Game();
  void fill(int, int, int, int);
  bool isRunning();
  void newPlayer(Player*);
  bool chargeGraphics();
  void eventHandler();
  void update();
  void render();
  SDL_Renderer* getRenderer();
  Texture* getTexture(int);
  void deleteTextures();
};

#endif
