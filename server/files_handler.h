#ifndef FILES_HANDLER_H
#define FILES_HANDLER_H

#include <mutex>
#include <string>

#include "hero.h"

class FilesHandler {
 private:
  std::mutex mutex;

 public:
  FilesHandler();
  ~FilesHandler();
  void save_player_status(Hero* hero);
  Hero* get_player_status(const std::string player_name,
                          Json::Value& entities_cfg);
};

#endif
