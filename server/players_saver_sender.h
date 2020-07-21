#ifndef PLAYERS_SAVER_SENDER_H
#define PLAYERS_SAVER_SENDER_H

#include <string>
#include <tuple>

#include "argentum_game.h"
#include "thread.h"

class PlayersSaverSender : public Thread {
 public:
  PlayersSaverSender(
      BlockingThreadSafeQueue<
          std::tuple<std::string, std::vector<unsigned char>> *>
          *players_serializations_queue,
      FilesHandler &files_handler);
  ~PlayersSaverSender() override;
  void run() override;
  void stop();

 private:
  BlockingThreadSafeQueue<std::tuple<std::string, std::vector<unsigned char>>
                              *> *players_serializations_queue;
  FilesHandler &files_handler;
  bool alive;
};

#endif
