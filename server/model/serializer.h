#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
#include <cstdint>
#include "argentum_game.h"
#include <arpa/inet.h>
class Serializer {
 public:
  static std::vector<unsigned char> serialize_game_status(ArgentumGame *game);
  static void debug_deserialize(std::vector<unsigned char> serialization);
};

#endif  // ARGENTUMGAME_H
