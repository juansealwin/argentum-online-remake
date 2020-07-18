#include "window_game.h"

WindowGame::WindowGame() {
  screen_width = 800;
  screen_height = 600;
  window_init();
}

WindowGame::~WindowGame() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  IMG_Quit();
  SDL_Quit();
  Mix_Quit();
  TTF_Quit();
}

void WindowGame::window_init() {
  window = SDL_CreateWindow("Argentum Online", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, screen_width,
                            screen_height, SDL_WINDOW_SHOWN);

  if (!window) {
    throw SdlException(MSG_ERROR_SDL_INIT_WINDOW, SDL_GetError());
  } else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      throw SdlException(MSG_ERROR_SDL_INIT_RENDERER, SDL_GetError());
    } else {
      // Fondo negro
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

      // Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags))
        throw SdlException(MSG_ERROR_SDL_IMG_INIT, IMG_GetError());

      // Inicializamos el mixer de audio
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw SdlException(MSG_ERROR_SDL_MIXER_INIT, Mix_GetError());

      // Inicializamos TTF
      if (TTF_Init() == -1)
        throw SdlException(MSG_ERROR_SDL_TTF_INIT, TTF_GetError());
    }
  }
}

SDL_Renderer* WindowGame::get_renderer() { return renderer; }