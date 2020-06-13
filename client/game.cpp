#include "game.h"

Game::Game(int width, int height) : screen_width(width), screen_height(height) {
  window = SDL_CreateWindow("Argentum Online", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_SHOWN);

  if (!window)
    throw SdlException("Error en la inicialización de la ventana",
                       SDL_GetError());
  else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
      throw SdlException("Error en la inicialización del render",
                         SDL_GetError());
    else
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  if (chargeGraphics())
    throw SdlException("Error al cargar las texturas", SDL_GetError());
  else
    is_running = true;
}

Game::~Game() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = NULL;
  }
  IMG_Quit();
  SDL_Quit();
  deleteTextures();
}

void Game::deleteTextures() {
  std::vector<Texture*>::iterator it;
  for (it = textures.begin(); it != textures.end();) {
    delete *it;
    it = textures.erase(it);
  }
}

// mejorar
bool Game::chargeGraphics() {
  textures.push_back(new Texture());
  textures.push_back(new Texture());
  textures.at(0)->loadTexture((std::string)PATH_GNOME_BODY, renderer);
  textures.at(1)->loadTexture((std::string)PATH_GNOME_HEAD, renderer);

  return EXIT_SUCCESS;
}

void Game::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
  SDL_RenderClear(renderer);
}

void Game::eventHandler() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    // User requests quit
    if (event.type == SDL_QUIT) {
      is_running = false;
    }
    // User presses a key
    else if (event.type == SDL_KEYDOWN) {
      // Select surfaces based on key press
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          body_player = player->move(MOVE_UP);
          head_player = player->getFaceProfile(MOVE_UP);
          break;

        case SDLK_DOWN:
          body_player = player->move(MOVE_DOWN);
          head_player = player->getFaceProfile(MOVE_DOWN);
          break;

        case SDLK_LEFT:
          body_player = player->move(MOVE_LEFT);
          head_player = player->getFaceProfile(MOVE_LEFT);
          break;

        case SDLK_RIGHT:
          body_player = player->move(MOVE_RIGHT);
          head_player = player->getFaceProfile(MOVE_RIGHT);
          break;

        default:
          break;
      }
    }
  }
}
// mejorar
void Game::update() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);
  textures.at(0)->render(renderer, &body_player,
                         screen_width / 2 - (player->getBodyW() / 2),
                         screen_height / 2 - (player->getBodyH() / 2));
  textures.at(1)->render(
      renderer, &head_player, screen_width / 2 - (player->getHeadW() / 2),
      screen_height / 2 - (player->getBodyH() / 2) - (player->getHeadH() / 2));
}

void Game::render() { SDL_RenderPresent(renderer); }

void Game::newPlayer(Player* new_player) { player = new_player; }

bool Game::isRunning() { return is_running; }

SDL_Renderer* Game::getRenderer() { return renderer; }

Texture* Game::getTexture(int index) { return textures.at(index); }
