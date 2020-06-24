#include "base_character.h"
#include <iostream>
BaseCharacter::BaseCharacter(int x, int y, int type, char repr, int max_hp,
                             int level, Map *map)
    : Entity(x, y, type, repr),
      max_hp(max_hp),
      level(level),
      current_hp(max_hp),
      map(map) {}

BaseCharacter::BaseCharacter(int x, int y, int type, char repr,
                             int level, Map *map)
    : Entity(x, y, type, repr),
      level(level),
      map(map) {}

void BaseCharacter::move(int next_x, int next_y) {
  if (map->can_ocupy_cell(next_x, next_y)) {
    map->ocupy_cell(next_x, next_y);
    map->empty_cell(x_position, y_position);
    x_position = next_x;
    y_position = next_y;
  }
}

BaseCharacter::~BaseCharacter() {}
