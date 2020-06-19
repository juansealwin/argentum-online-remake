#include "game_renderer.h"

GameRenderer::GameRenderer(int width, int height)
    : screen_width(width), screen_height(height) {
  windowInit();
  player = nullptr;
  current_map = new Map(ID_MAP_GRASS, renderer, screen_width, screen_height);
  /*current_map = new Map(ID_MAP_GRASS, renderer, screen_width, screen_height);

  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250, 128);
  current_map->loadCharacter(renderer, ID_PRIEST, 280, 128);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320, 128);
  current_map->loadCharacter(renderer, ID_BANKER, 360, 128);
  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128 + 100);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128 + 100);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128 + 100);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250, 128);
  current_map->loadCharacter(renderer, ID_PRIEST, 280, 128 + 100);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320, 128 + 100);
  current_map->loadCharacter(renderer, ID_BANKER, 360, 128 + 100);
  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128 + 300);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128 + 300);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128 + 200);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250 + 50, 128 + 250);
  current_map->loadCharacter(renderer, ID_PRIEST, 280 + 200, 128 + 200);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320 + 300, 128 + 200);
  current_map->loadCharacter(renderer, ID_BANKER, 360 + 300, 128 + 300);
  player = new Gnome(renderer, screen_width / 2, screen_height / 2);*/
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

void GameRenderer::run() {
  SDL_RenderClear(renderer);
  current_map->render();
  player->renderAsHero();
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