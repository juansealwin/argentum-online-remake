#ifndef CHARACTER_STATUS_H
#define CHARACTER_STATUS_H

#include "types.h"
#include "character.h"

class CharacterStatus {
 private:
  character_t type_character;
  int x;
  int y;
  bool is_alive;
  id_texture_t spellbound;
  int lifetime;

 public:
  CharacterStatus();
  CharacterStatus(int, int, int/*, int*/);
  ~CharacterStatus();
  CharacterStatus& operator=(const CharacterStatus&);
  bool is_equal(CharacterStatus);
  int get_x() const;
  int get_y() const;
  character_t get_type_character() const;
  id_texture_t is_afected() const;
  int get_life_time() const;
};

#endif
