#include "event_handler.h"

EventHandler::EventHandler(int id, BlockingQueue& queue) : id_player(id),queue_events(queue) {
  is_running = true;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
  try {
    SDL_Event event;
    Event send_event;
    while (is_running) {
      while (SDL_PollEvent(&event) != 0) {
        // User requests quit
        if (event.type == SDL_QUIT) {
          is_running = false;
          //queue_events.pushEvent();
          break;
          
        }
        // User presses a key
        else if (event.type == SDL_KEYDOWN) {
          // Select surfaces based on key press
          switch (event.key.keysym.sym) {
            case SDLK_UP:
              //queue_evets.
              //player->move(MOVE_UP);
              //current_map->update(0, -TILE_SIZE);
              break;

            case SDLK_DOWN:
              //player->move(MOVE_DOWN);
              //current_map->update(0, TILE_SIZE);
              break;

            case SDLK_LEFT:
              //player->move(MOVE_LEFT);
              //current_map->update(-TILE_SIZE, 0);
              break;

            case SDLK_RIGHT:
              //player->move(MOVE_RIGHT);
              //current_map->update(TILE_SIZE, 0);
              break;
          }
        }
      }
    }

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}