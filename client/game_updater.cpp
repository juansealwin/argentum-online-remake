#include "game_updater.h"

GameUpdater::GameUpdater(int id, int width, int height, BlockingMap& block_map)
    : id_hero(id), screen_width(width), screen_height(height), blocking_map(block_map) {
  window_init();
  
  current_map = new Map(id_hero, ID_MAP_GRASS, renderer, 800, 600);
}

// GameUpdater::~GameUpdater() {}

void GameUpdater::run() {
  try {
    while (is_running) {
      // Recibimos las entidades dentro del mapa con sus cambios
      blocking_map.update_map(next_status);

      std::map<int, CharacterStatus>::iterator it;
      std::map<int, CharacterStatus>::iterator it2;

      for (it = next_status.begin(); it != next_status.end(); it++) {
        // Chequeamos si dicho personaje ya existia dentro del mapa
        it2 = current_status.find(it->first);

        if (it2 != current_status.end()) {
          // Chequeamos si dicho personaje se mantuvo cte. o se modifico
          if (!(it2->second.is_equal(it->second))) {
            // Si cambio hacemos un update del personaje
            current_map->update_character(it->first, it->second.get_x(),
                                        it->second.get_y());
            // Mofificamos el status para la proxima pasada
            it2->second = it->second;
          }
        } else {
          // Como no existe lo creamos
          current_map->load_character(renderer, it->second.get_type_character(),
                                    it->first, it->second.get_x(),
                                    it->second.get_y());
        }
      }
      // No deberia hacer el render, por ahora queda asi
      current_map->render();
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

/* Lo de aca para abajo habria que pasarlo al GameRenderer en un futuro */

void GameUpdater::window_init() {
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

GameUpdater::~GameUpdater() {
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
