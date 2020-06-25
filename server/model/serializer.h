#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
#include <cstdint>
#include "argentum_game.h"
#include <arpa/inet.h>
class Serializer {
 public:
  static std::vector<unsigned char> serialize_game_status(ArgentumGame *game);
};

#endif  // ARGENTUMGAME_H
