#ifndef FILES_HANDLER_H
#define FILES_HANDLER_H

#include <mutex>
#include <vector>

#include "hero.h"

class FilesHandler {
 private:
  std::mutex mutex;

 public:
  FilesHandler();
  ~FilesHandler();
  void save_player_status(Hero* hero);
};

#endif
