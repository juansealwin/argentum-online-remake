#include "game.h"
/*
Game::Game(int width, int height) : screen_width(width), screen_height(height) {
  windowInit();
  current_map = new Map(ID_MAP_GRASS, renderer, screen_width, screen_height);

  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250, 128);
  current_map->loadCharacter(renderer, ID_PRIEST, 280, 128);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320, 128);
  current_map->loadCharacter(renderer, ID_BANKER, 360, 128);
  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128+100);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128+100);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128+100);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250, 128);
  current_map->loadCharacter(renderer, ID_PRIEST, 280, 128+100);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320, 128+100);
  current_map->loadCharacter(renderer, ID_BANKER, 360, 128+100);
  current_map->loadCharacter(renderer, ID_SPIDER, 128, 128+300);
  current_map->loadCharacter(renderer, ID_SKELETON, 160, 128+300);
  current_map->loadCharacter(renderer, ID_GOBLIN, 200, 128+200);
  current_map->loadCharacter(renderer, ID_ZOMBIE, 250+50, 128+250);
  current_map->loadCharacter(renderer, ID_PRIEST, 280+200, 128+200);
  current_map->loadCharacter(renderer, ID_MERCHANT, 320+300, 128+200);
  current_map->loadCharacter(renderer, ID_BANKER, 360+300, 128+300);
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
      // Fondo negro
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

    is_running = true;
  }
}


void Game::deleteTextures() {
  std::vector<Texture*>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    (*it)->free();
    delete (*it);
    it = textures.erase(it);
  }
}

void Game::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
  SDL_RenderClear(renderer);
}
*/

Game::~Game() {}

Game::Game(int id, BlockingQueue& queue) : id_player(id), events_queue(queue) {}

void Game::event_handler() {
  try {
    SDL_Event event;
    while (is_running) {
      while (SDL_PollEvent(&event) != 0) {
        // User requests quit
        if (event.type == SDL_QUIT) {
          is_running = false;
          // queue_events.pushEvent();
          break;

        }
        // User presses a key
        else if (event.type == SDL_KEYDOWN) {
          // Select surfaces based on key press
          if (event.key.keysym.sym == SDLK_UP) {
            Event send_event(id_player, move_up);
            events_queue.push_event(send_event);
          }
          if (event.key.keysym.sym == SDLK_DOWN) {
            Event send_event(id_player, move_down);
            events_queue.push_event(send_event);
          }
          if (event.key.keysym.sym == SDLK_LEFT) {
            Event send_event(id_player, move_left);
            events_queue.push_event(send_event);
          }
          if (event.key.keysym.sym == SDLK_RIGHT) {
            Event send_event(id_player, move_right);
            events_queue.push_event(send_event);
          }
        }
      }
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

bool Game::is_up() { return is_running; }
/*
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
          current_map->update(0, -TILE_SIZE);
          break;

        case SDLK_DOWN:
          player->move(MOVE_DOWN);
          current_map->update(0, TILE_SIZE);
          break;

        case SDLK_LEFT:
          player->move(MOVE_LEFT);
          current_map->update(-TILE_SIZE, 0);
          break;

        case SDLK_RIGHT:
          player->move(MOVE_RIGHT);
          current_map->update(TILE_SIZE, 0);
          break;

        default:
          break;
      }
    }
  }
}*/
// mejorar
/*
void Game::update() {}

void Game::render() {
  SDL_RenderClear(renderer);
  current_map->render();
  player->renderAsHero();
  SDL_RenderPresent(renderer);
}

void Game::newPlayer(PlayableCharacter* new_player) { player = new_player; }



SDL_Renderer* Game::getRenderer() { return renderer; }

Texture* Game::getTexture(int index) { return textures.at(index); }
*/
