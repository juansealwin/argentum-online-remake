#include "character_status.h"

CharacterStatus::CharacterStatus(int type_char, int new_x, int new_y)
    : x(new_x), y(new_y) {
  // poner los id que usa el server
  switch (type_char) {
    case 1112:
      break;
  }
}

CharacterStatus::~CharacterStatus() {}

void CharacterStatus::operator=(CharacterStatus other_status) {
  type_character = other_status.type_character;
  x = other_status.x;
  y = other_status.y;
  is_alive = other_status.is_alive;
}

bool CharacterStatus::isEqual(CharacterStatus other_status) {
  return (type_character == other_status.type_character &&
          x == other_status.x && y == other_status.y &&
          is_alive == other_status.is_alive)
             ? true
             : false;
}