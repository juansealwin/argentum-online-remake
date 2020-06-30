#include "event_handler.h"

EventHandler::~EventHandler() {}

EventHandler::EventHandler(const int player_id,
                           CommandsBlockingQueue& commands_queue,
                           EventsQueue& queue, bool& run)
    : player_id(player_id),
      commands_queue(commands_queue),
      events_queue(queue),
      is_running(run) {}

void EventHandler::get_events() {
  try {
    //background_music.set_music("musica_lobby.wav");
    //background_music.play_music();
    SDL_Event event;
    while (is_running) {
      while (SDL_PollEvent(&event) != 0) {
        // User requests quit
        if (event.type == SDL_QUIT) {
          is_running = false;
          QuitCommandDTO* quit_command = new QuitCommandDTO();
          commands_queue.push(quit_command);
          // Aviso al renderer que hay que cerrar
          events_queue.push(EVENT_QUIT);
          break;
        }
        // User presses a key
        //else if (event.type == SDL_KEYDOWN) {
          // Select surfaces based on key press
          if (event.key.keysym.sym == SDLK_UP) {
            MoveCommandDTO* move_command =
                new MoveCommandDTO(player_id, move_up);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_DOWN) {
            MoveCommandDTO* move_command =
                new MoveCommandDTO(player_id, move_down);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_LEFT) {
            MoveCommandDTO* move_command =
                new MoveCommandDTO(player_id, move_left);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_RIGHT) {
            MoveCommandDTO* move_command =
                new MoveCommandDTO(player_id, move_right);
            commands_queue.push(move_command);
          }
        //}
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

bool EventHandler::is_up() { return is_running; }
