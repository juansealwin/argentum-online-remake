#include "character_status.h"

CharacterStatus::CharacterStatus() {}

CharacterStatus::CharacterStatus(int type_char, int new_x, int new_y, int spell)
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

    case 29:
      type_character = GOBLIN;
      break;

    case 30:
      type_character = SPIDER;
      break;

    case 31:
      type_character = SKELETON;
      break;

    case 32:
      type_character = ZOMBIE;
      break;

    case 33:
      type_character = PRIEST;
      break;

    case 34:
      type_character = MERCHANT;
      break;

    case 35:
      type_character = BANKER;
      break;
  }
  switch (spell) {
    case 0:
      spellbound = ID_NULL;
      lifetime = 0;
      break;

    case 1:
      spellbound = ID_BLEEDING;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_BLEDDING;
      break;

    case 2:
      spellbound = ID_MAGIC_ARROW;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_MAGIC_ARROW;
      break;

    case 3:
      spellbound = ID_HEAL;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_HEAL;
      break;

    case 4:
      spellbound = ID_ELECTRIC_SHOCK;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_ELECTRIC_SHOCK;
      break;

    case 5:
      spellbound = ID_EXPLOSION;
      lifetime = FRAMES_PER_TEXTURE * FRAMES_EXPLOSION;
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
  spellbound = other_status.spellbound;
  lifetime = lifetime;
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

id_texture_t CharacterStatus::is_afected() const { return spellbound; }

int CharacterStatus::get_life_time() const { return lifetime; }