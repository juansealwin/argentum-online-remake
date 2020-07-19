#ifndef FILES_HANDLER_H
#define FILES_HANDLER_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <vector>

#include "deserializer.h"
#include "hero.h"
#include "serializer.h"

class FilesHandler {
 private:
  std::mutex mutex;

 public:
  FilesHandler();
  ~FilesHandler();
  void save_player_status(Hero* hero);
  Hero* get_player_status(const std::string player_name);
};

#endif
