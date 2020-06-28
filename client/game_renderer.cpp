#include "game_renderer.h"

GameRenderer::GameRenderer(int width, int height, ProtectedMap& prot_map)
    : screen_width(width), screen_height(height), protected_map(prot_map) {
  window_init();
}

void GameRenderer::window_init() {
  window = SDL_CreateWindow("Argentum Online", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, screen_width,
                            screen_height, SDL_WINDOW_SHOWN);

  if (!window) {
    throw SdlException("Error en la inicialización de la ventana",
                       SDL_GetError());
  } else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      throw SdlException("Error en la inicialización del render",
                         SDL_GetError());
    } else {
      // Fondo negro
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    }

    is_running = true;
  }
}

GameRenderer::~GameRenderer() {
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
}

// Hay que pasarle el renderer a los objetos y hay que hacer swap de renderers
// entre el actual y el del updater
void GameRenderer::run() {
  try {
    texture_manager.load_textures(renderer);
    Uint32 frame_start;

    int frame_time;
    while (is_running) {
      frame_start = SDL_GetTicks();
      Game current_game = protected_map.map_reader();
      SDL_RenderClear(renderer);
      current_game.render(renderer);
      // creo que no va a hacer falta
      // player.render_as_hero(renderer);
      SDL_RenderPresent(renderer);

      frame_time = SDL_GetTicks() - frame_start;
      if (FRAME_DELAY > frame_time) SDL_Delay(FRAME_DELAY - frame_time);
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

/*

void Game::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
  SDL_RenderClear(renderer);
}

*/

SDL_Renderer* GameRenderer::get() {return renderer;}