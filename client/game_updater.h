#ifndef GAME_UPDATER_H
#define GAME_UPDATER_H

#include "thread.h"

class GameUpdater : public Thread{
 private:
  /* data */
 public:
  GameUpdater(/* args */);
  ~GameUpdater();
  void run();
};

#endif