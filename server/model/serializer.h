#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
#include <cstdint>
#include "argentum_game.h"
#include <arpa/inet.h>
#include <algorithm>
class Serializer {
 public:
  static std::vector<unsigned char> serialize_game_status(ArgentumGame *game);
  static std::vector<unsigned char> serialize_game_status_v2(ArgentumGame *game);
  static void debug_deserialize(std::vector<unsigned char> serialization);

 private:
  //  //deben coincidir con los config del json
  // static bool is_hero(uint8_t t);
  // static bool is_npc(uint8_t t);
  static bool is_monster(uint8_t t);
  static bool vector_contains(std::vector<uint8_t> v, uint8_t x);
  // //serializan atributos y los inserta al final del vector
  static void serialize_monster(std::vector<unsigned char> &serialization, Monster *m);

};

#endif  // ARGENTUMGAME_H
