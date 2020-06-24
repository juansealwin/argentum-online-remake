#include "character_status.h"

CharacterStatus::CharacterStatus() {}

CharacterStatus::CharacterStatus(int type_char, int new_x, int new_y)
    : x(new_x), y(new_y) {
  // poner los id que usa el server
  switch (type_char) {
    case 25:
      type_character = HUMAN;
      break;

    case 26:
      type_character = ELF;
      break;

    case 27:
      type_character = DWARF;
      break;

    case 28:
      type_character = GNOME;
      break;

    case 1288:
      type_character = ZOMBIE;
      break;

    case 1677:
      type_character = GOBLIN;
      break;

    case 1712:
      type_character = SPIDER;
      break;

    case 1750:
      type_character = SKELETON;
      break;

    case 1221:
      type_character = MERCHANT;
      break;

    case 1222:
      type_character = BANKER;
      break;

    case 1223:
      type_character = PRIEST;
      break;
  }
}

CharacterStatus::~CharacterStatus() {}

CharacterStatus& CharacterStatus::operator=(
    const CharacterStatus& other_status) {
  type_character = other_status.type_character;
  x = other_status.x;
  y = other_status.y;
  is_alive = other_status.is_alive;
}

bool CharacterStatus::is_equal(CharacterStatus other_status) {
  return (type_character == other_status.type_character &&
          x == other_status.x && y == other_status.y &&
          is_alive == other_status.is_alive);
}

character_t CharacterStatus::get_type_character() const {
  return type_character;
}

int CharacterStatus::get_x() const { return x; }

int CharacterStatus::get_y() const { return y; }
