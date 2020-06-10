#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <SDL2/SDL.h>

#include <vector>
#include "texture.h"
#include "exception_messages.h"
#include "sdl_exception.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"
#define PATH_HUMAN "humano.png"

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
    void GameWindow::chargeGraphics();
    SDL_Renderer* getRenderer();
};

#endif
