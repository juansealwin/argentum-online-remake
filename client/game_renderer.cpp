#include "game_renderer.h"

GameRenderer::GameRenderer(int width, int height, ProtectedMap& prot_map,
                           EventsQueue& queue)
    : screen_width(width),
      screen_height(height),
      protected_map(prot_map),
      events_queue(queue) {
  window_init();
  is_running = true;
}

void GameRenderer::window_init() {
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
  Mix_Quit();
  TTF_Quit();
}

void GameRenderer::run() {
  try {
    // Cargamos todas las texturas del juego
    texture_manager.load_textures(renderer);
    int frame_start;
    int frame_time;
    // Leemos la primera instancia que nos manda el server
    Game current_game = protected_map.map_reader(ui);
    event_t local_event;

    while (is_running) {
      frame_start = SDL_GetTicks();

      // Vemos si hay algun evento local
      local_event = events_queue.pop();
      if (local_event) {
        switch (local_event) {
          case EVENT_QUIT:
            is_running = false;
            break;
        }
      }

      // Leemos las actualizaciones mandadas desde el server
      current_game = protected_map.map_reader(ui);
      
      // Limpiamos el renderer
      SDL_RenderClear(renderer);
      
      // Renderizamos el mapa en su estado actual
      current_game.render(renderer);
      
      // Renderizamos la UI con sus valores actualizados
      ui.render(renderer);

      SDL_RenderPresent(renderer);

      // Vemos si el hilo debe dormirse para que el frame rate se mantenga cte.
      frame_time = SDL_GetTicks() - frame_start;
      int to_sleep = FRAME_DELAY - frame_time;
      if (to_sleep > 0) {
        SDL_Delay(to_sleep);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}
