
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <stdint.h>

#include <iostream>
#include <string>
#include <vector>

#include "hero.h"

class Hero;

class Deserializer {
 public:
  // static void deserialize_bank_of_hero(
  //     std::vector<unsigned char> &serialization, Hero *h);
  static Hero *deserialize_hero(std::vector<unsigned char> &serialization);
};

#endif
