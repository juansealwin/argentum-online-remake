#include "game.h"

Game::Game(int width, int height) : screen_width(width), screen_height(height) {
  windowInit();
  background = new BackgroundMap("mapa_hierba.png", renderer, screen_width,
                                 screen_height);
  player = new Gnome(renderer, screen_width / 2, screen_height / 2);
}

void Game::windowInit() {
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
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  }
  /*if (chargeGraphics())
    throw SdlException("Error al cargar las texturas", SDL_GetError());
  else*/
  is_running = true;
}

Game::~Game() {
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
  // background->~BackgroundMap();
  background = nullptr;
  // player->~Player();
  player = nullptr;
}

void Game::deleteTextures() {
  std::vector<Texture*>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    (*it)->free();
    delete (*it);
    it = textures.erase(it);
  }
}

// mejorar
/*bool Game::chargeGraphics() {
  textures.push_back(new Texture());
  textures.push_back(new Texture());
  textures.at(0)->loadTexture((std::string)PATH_GNOME_BODY, renderer);
  textures.at(1)->loadTexture((std::string)PATH_GNOME_HEAD, renderer);

  return EXIT_SUCCESS;
}*/

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
          player->move(MOVE_UP);
          player->updateFaceProfile(MOVE_UP);
          background->update(0, -32);
          break;

        case SDLK_DOWN:
          player->move(MOVE_DOWN);
          player->updateFaceProfile(MOVE_DOWN);
          background->update(0, 32);
          break;

        case SDLK_LEFT:
          player->move(MOVE_LEFT);
          player->updateFaceProfile(MOVE_LEFT);
          background->update(-32, 0);
          break;

        case SDLK_RIGHT:
          player->move(MOVE_RIGHT);
          player->updateFaceProfile(MOVE_RIGHT);
          background->update(32, 0);
          break;

        default:
          break;
      }
    }
  }
}
// mejorar
void Game::update() {}

void Game::render() {
  // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);
  background->render();
  player->render();
  SDL_RenderPresent(renderer);
}

void Game::newPlayer(Player* new_player) { player = new_player; }

bool Game::isRunning() { return is_running; }

SDL_Renderer* Game::getRenderer() { return renderer; }

Texture* Game::getTexture(int index) { return textures.at(index); }
