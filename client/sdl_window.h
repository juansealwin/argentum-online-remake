#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H
#include <SDL2/SDL.h>
#include "sdl_exception.h"
#include "exception_messages.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "Argentum_online.jpg"

class SdlWindow {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int screen_width = 800;
        int screen_height = 600;
        void fill(int, int, int, int);

    public:
        SdlWindow(int, int);
        ~SdlWindow();
        void fill();
        void render();
        SDL_Renderer* getRenderer();
};

#endif
