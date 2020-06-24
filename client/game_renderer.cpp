#include "game_renderer.h"

GameRenderer::GameRenderer(int width, int height, PlayableCharacter& hero,
                           ProtectedMap& prot_map)
    : screen_width(width),
      screen_height(height),
      player(hero),
      protected_map(prot_map) {
  current_game = nullptr;
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
  // current_map = nullptr;
  // player = nullptr;
}

// Hay que pasarle el renderer a los objetos y hay que hacer swap de renderers
// entre el actual y el del updater
void GameRenderer::run() {
  SDL_RenderClear(renderer);
  current_game->render();
  player.render_as_hero();
  SDL_RenderPresent(renderer);
}

/*

void Game::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
  SDL_RenderClear(renderer);
}


// void Game::newPlayer(PlayableCharacter* new_player) { player = new_player; }

// SDL_Renderer* GameRenderer::getRenderer() { return renderer; }

// Texture* GameRenderer::getTexture(int index) { return textures.at(index); }
*/