#ifndef CHARACTER_STATUS_H
#define CHARACTER_STATUS_H

#include "character.h"

class CharacterStatus {
 private:
  character_t type_character;
  int x;
  int y;
  bool is_alive;

 public:
  CharacterStatus(int, int, int);
  ~CharacterStatus();
  void operator=(CharacterStatus);
  bool isEqual(CharacterStatus);
};



#endif