#include "base_character.h"

#include <iostream>
BaseCharacter::BaseCharacter(unsigned int unique_id, int x, int y,
                             unsigned int type, char repr, unsigned int max_hp,
                             unsigned int level, Map *map)
    : Entity(unique_id, x, y, type, repr),
      current_hp(max_hp),
      max_hp(max_hp),
      level(level),
      affected_by(0),
      map(map) {}

BaseCharacter::BaseCharacter(unsigned int unique_id, int x, int y,
                             unsigned int type, char repr, unsigned int level,
                             Map *map)
    : Entity(unique_id, x, y, type, repr),
      level(level),
      affected_by(0),
      map(map) {}

void BaseCharacter::move(int next_x, int next_y) {
  if (map->can_ocupy_cell(next_x, next_y)) {
    map->ocupy_cell(next_x, next_y, unique_id);
    map->empty_cell(x_position, y_position);
    change_orientation(x_position, y_position, next_x, next_y);
    x_position = next_x;
    y_position = next_y;
  }
}

void BaseCharacter::change_orientation(int old_x, int old_y, int new_x,
                                       int new_y) {
  int x_diff = old_x - new_x;
  int y_diff = old_y - new_y;
  if (x_diff > 0)
    orientation = orientation_down;  // se movio hacia abajo
  else if (x_diff < 0)
    orientation = orientation_up;  // hacia arriba
  else if (y_diff > 0)
    orientation = orientation_right;  // derecha
  else if (y_diff < 0)
    orientation = orientation_left;
}

void BaseCharacter::clear_effects() {
  if (affected_by != 0) {
    std::cout << "cleared effect!" << std::endl;
  }
  affected_by = 0;
  
}

BaseCharacter::~BaseCharacter() {}
