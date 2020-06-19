#include "event_handler.h"

EventHandler::EventHandler(int id, BlockingQueue& queue)
    : id_player(id), queue_events(queue) {
  is_running = true;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
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
            queue_events.pushEvent(send_event);
          }
          if (event.key.keysym.sym == SDLK_DOWN) {
            Event send_event(id_player, move_down);
            queue_events.pushEvent(send_event);
          }
          if (event.key.keysym.sym == SDLK_LEFT) {
            Event send_event(id_player, move_left);
            queue_events.pushEvent(send_event);
          }
          if (event.key.keysym.sym == SDLK_RIGHT) {
            Event send_event(id_player, move_right);
            queue_events.pushEvent(send_event);
          }
        }
      }
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}