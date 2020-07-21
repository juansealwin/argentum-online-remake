#ifndef PLAYERS_SAVER_SENDER_H
#define PLAYERS_SAVER_SENDER_H

#include <chrono>
#include <string>
#include <tuple>

#include "argentum_game.h"
#include "thread.h"

class PlayersSaverSender : public Thread {
 public:
  PlayersSaverSender(BlockingThreadSafeQueue<
                         std::tuple<std::string, std::vector<unsigned char>> *>
                         *players_serializations_queue,
                     FilesHandler &files_handler, bool periodic_mode,
                     std::vector<ArgentumGame *> &rooms);
  ~PlayersSaverSender() override;
  void run() override;

 private:
  BlockingThreadSafeQueue<std::tuple<std::string, std::vector<unsigned char>> *>
      *players_serializations_queue;
  FilesHandler &files_handler;
  bool alive;
  bool periodic_mode;
  std::vector<ArgentumGame *> &rooms;
  std::chrono::time_point<std::chrono::high_resolution_clock> last_update_time;
};

#endif
