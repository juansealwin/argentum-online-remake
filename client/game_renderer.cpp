#include "game_renderer.h"

GameRenderer::GameRenderer(SDL_Renderer* ren, int width, int height,
                           ProtectedMap& prot_map, EventsQueue& queue)
    : renderer(ren),
      screen_width(width),
      screen_height(height),
      protected_map(prot_map),
      events_queue(queue) {
  is_running = true;
}

GameRenderer::~GameRenderer() {}

void GameRenderer::run() {
  try {
    // Cargamos todas las texturas del juego
    texture_manager.load_textures(renderer);
    int frame_start;
    int frame_time;
    // Para saber las dimensiones de la ventana de juego
    SDL_Rect window_size = {0, 0, screen_width, screen_height};
    // Leemos la primera instancia que nos manda el server
    Game current_game;
    protected_map.map_reader(current_game, ui, current_sounds);
    SoundManager sound_manager;
    sound_manager.play_music(BG_MUSIC_1);
    event_t local_event;
    int index;
    bool is_selected = false;
    int item_selected = 20;  // TODO: aclarar que hace
    std::string input_message = "";

    while (is_running) {
      frame_start = SDL_GetTicks();

      // Vemos si hay algun evento local
      local_event = events_queue.pop(index);
      if (local_event) {
        switch (local_event) {
          case EVENT_QUIT:
            is_running = false;
            break;

          case EVENT_SELECT_ITEM:
            if (is_selected) {
              if (index == item_selected) {
                is_selected = false;
              } else {
                item_selected = index;
              }
            } else {
              item_selected = index;
              is_selected = true;
            }
            break;

          case EVENT_MESSAGE:
            input_message = events_queue.read_message();
            // Para que no quede un string vacio ya que no se puede renderizar
            if (input_message.size() == 0) input_message = " ";
            break;

          default:
            break;
        }
      }

      // Leemos las actualizaciones mandadas desde el server
      protected_map.map_reader(current_game, ui, current_sounds);

      // Actualizamos el estado del inventario para el EventHandler
      events_queue.write_status(ui);

      // Limpiamos el renderer
      SDL_RenderClear(renderer);

      // Renderizamos el mapa en su estado actual
      current_game.render(renderer);

      // Renderizamos la UI con sus valores actualizados
      ui.render(renderer, window_size, input_message, is_selected,
                item_selected);

      // Renderizamos todo lo de esta pasada
      SDL_RenderPresent(renderer);

      // Reproducimos los sonidos que fueron agregados al vector
      sound_manager.play_sound_effects(current_sounds);

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
