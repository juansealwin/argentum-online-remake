#include "game_updater.h"

GameUpdater::GameUpdater(BlockingMap& map, Map& new_map)
    : map_updated(map), current_map(new_map) {}

GameUpdater::~GameUpdater() {}

void GameUpdater::run() {
  try {
    while (is_running) {
      map_updated.updateMap(next_map);
      std::map<int, std::pair<int, int>>::iterator it;

      /*for (it = map_updated.begin(); it != map_updated.end(); it++) {
        it->
      }*/
      // Event event = new_events.popEvent();
      // if (event.isEnding()) is_running = false;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}