#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <vector>
#include <cstdint>
#include "argentum_game.h"
#include <arpa/inet.h>
#include <algorithm>
#include "drop.h"
class Serializer {
 public:
  static std::vector<unsigned char> serialize_game_status(ArgentumGame *game);
  static std::vector<unsigned char> serialize_game_status_v2(ArgentumGame *game);
  static std::vector<unsigned char> serialize_game_status_v3(ArgentumGame *game);

  static void debug_deserialize(std::vector<unsigned char> serialization);
  static void debug_deserialize_v3(std::vector<unsigned char> serialization);


 private:
  //  //deben coincidir con los config del json
  static void serialize_common_fields(std::vector<unsigned char> &serialization, uint16_t uid, Entity *entity);
  static void serialize_common_fields_v2(std::vector<unsigned char> &serialization, uint16_t uid, Entity *entity);
  static void serialize_drop();
  static bool is_hero(uint8_t t);
  static bool is_drop(uint8_t t);
  // static bool is_npc(uint8_t t);
  static bool is_monster(uint8_t t);
  static bool vector_contains(std::vector<uint8_t> v, uint8_t x);
  // //serializan atributos y los inserta al final del vector
  static void serialize_monster(std::vector<unsigned char> &serialization, Monster *m);
  static void serialize_hero(std::vector<unsigned char> &serialization, Hero *m);
  static void serialize_drop(std::vector<unsigned char> &serialization, Drop* drop, std::tuple<unsigned int, unsigned int> coordinates);
};

#endif  // ARGENTUMGAME_H
