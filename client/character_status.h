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
  CharacterStatus();
  CharacterStatus(int, int, int);
  ~CharacterStatus();
  void operator=(CharacterStatus);
  bool is_equal(CharacterStatus);
  character_t get_type_character() const;
  int get_x() const;
  int get_y() const;
};



#endif