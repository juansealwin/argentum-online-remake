#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <vector>

#include "hero.h"

class Deserializer {
 public:
  static void deserialize_bank_of_hero(
      std::vector<unsigned char> &serialization, Hero *h);
  static Hero *deserialize_hero(std::vector<unsigned char> &serialization);

 private:
};

#endif