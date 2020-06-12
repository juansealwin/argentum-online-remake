#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <SDL2/SDL.h>

#include <vector>
#include "texture.h"
#include "exception_messages.h"
#include "sdl_exception.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"
#define PATH_HUMAN_BODY "humano.png"
#define PATH_HUMAN_HEAD "cabeza_humano.png"
#define PATH_ELF_BODY "elfo.png"
#define PATH_ELF_HEAD "cabeza_elfo.png"

class GameWindow {
   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Texture*> texturas;
    int screen_width = 800;
    int screen_height = 600;
    void fill(int, int, int, int);

   public:
    GameWindow(int, int);
    ~GameWindow();
    void fill();
    void render();
    void chargeGraphics();
    SDL_Renderer* getRenderer();
    Texture* getTexture(int);
};

#endif
