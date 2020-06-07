#ifndef __CLIENT_SDL_WINDOW_H__
#define __CLIENT_SDL_WINDOW_H__
#include <SDL2/SDL.h>
#include "../common/common_sdl_exception.h"
#include "../common/common_exception_messages.h"
#define GAME_NAME "Argentum"
#define PATH_IMG_LOBBY "cliente/assets/Argentum_online.jpg"

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
