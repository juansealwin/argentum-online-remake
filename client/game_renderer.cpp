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
    // Para saber las dimensiones de la ventana de juego
    SDL_Rect window_size = {0, 0, screen_width, screen_height};
    // Leemos la primera instancia que nos manda el server
    Game current_game;
    protected_map.map_reader(current_game, ui, current_sounds);
    SoundManager sound_manager;
    sound_manager.play_music();
    sound_manager.decrease_music_volume(100);
    event_t local_event;
    int index;
    // No hay items seleccionado entonces dejamos a item_selected en -1
    bool is_selected = false;
    int item_selected = -1;
    std::string input_message;

    while (is_running) {
      int frame_start = SDL_GetTicks();
      int frame_time = 0;
      // Vemos si hay algun evento local
      local_event = events_queue.pop(index);
      if (local_event) {
        switch (local_event) {
          case EVENT_QUIT:
            is_running = false;
            break;

          case EVENT_SELECT_ITEM:
            // Habia un item seleccionado
            if (is_selected) {
              // Se selecciono un item ya seleccionado
              if (index == item_selected) {
                is_selected = false;
              }
              // Se selecciono un item distinto al seleccionado
              else {
                item_selected = index;
              }
              // No habia item seleccionado
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

          case EVENT_INCREASE_MUSIC_VOLUME:
            sound_manager.increase_music_volume();
            break;

          case EVENT_DECREASE_MUSIC_VOLUME:
            sound_manager.decrease_music_volume();
            break;

          case EVENT_STOP_MUSIC:
            sound_manager.stop_music();
            break;

          case EVENT_PLAY_MUSIC:
            sound_manager.play_music();
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
