#include "game_renderer.h"

GameRenderer::GameRenderer(int width, int height, PlayableCharacter& hero,
                           Map& map)
    : screen_width(width),
      screen_height(height),
      player(hero),
      current_map(map) {
  windowInit();
}

void GameRenderer::windowInit() {
  window = SDL_CreateWindow("Argentum Online", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, screen_width,
                            screen_height, SDL_WINDOW_SHOWN);

  if (!window)
    throw SdlException("Error en la inicialización de la ventana",
                       SDL_GetError());
  else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
      throw SdlException("Error en la inicialización del render",
                         SDL_GetError());
    else
      // Fondo negro
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

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

/*
void GameRenderer::deleteTextures() {
  std::vector<Texture*>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    (*it)->free();
    delete (*it);
    it = textures.erase(it);
  }
}
*/

// Hay que pasarle el renderer a los objetos y hay que hacer swap de renderers
// entre el actual y el del updater
void GameRenderer::run() {
  SDL_RenderClear(renderer);
  current_map.render();
  player.renderAsHero();
  SDL_RenderPresent(renderer);
}

/*
void Game::render() {
  SDL_RenderClear(renderer);
  current_map->render();
  player->renderAsHero();
  SDL_RenderPresent(renderer);
}*/

// void Game::newPlayer(PlayableCharacter* new_player) { player = new_player; }

// SDL_Renderer* GameRenderer::getRenderer() { return renderer; }

// Texture* GameRenderer::getTexture(int index) { return textures.at(index); }