#include "base_character.h"
#include <iostream>

BaseCharacter::BaseCharacter(unsigned int unique_id, int x, int y,
                             unsigned int type, char repr, unsigned int max_hp,
                             unsigned int level, Map *map, const std::string &name)
    : Entity(unique_id, x, y, type, repr, orientation_down),
      current_hp(max_hp),
      max_hp(max_hp),
      level(level),
      affected_by(0),
      map(map),
      name(name) {}

bool BaseCharacter::move(int next_x, int next_y) {
  change_orientation(x_position, y_position, next_x, next_y);
  if (map->can_ocupy_cell(next_x, next_y)) {
    map->ocupy_cell(next_x, next_y, unique_id);
    map->empty_cell(x_position, y_position);
    x_position = next_x;
    y_position = next_y;
    return true;
  }
  return false;
}

void BaseCharacter::change_orientation(int old_x, int old_y, int new_x,
                                       int new_y) {
  int x_diff = old_x - new_x;
  int y_diff = old_y - new_y;
  if (x_diff > 0)
    orientation = orientation_up;  // se movio hacia abajo
  else if (x_diff < 0)
    orientation = orientation_down;  // hacia arriba
  else if (y_diff > 0)
    orientation = orientation_left;  // derecha
  else if (y_diff < 0)
    orientation = orientation_right;
}

void BaseCharacter::clear_effects() {
  affected_by = 0;
}

void BaseCharacter::set_position(int x, int y) {
  x_position = x;
  y_position = y;
}

void BaseCharacter::set_map(Map *map) {
  this->map = map;
}

std::string BaseCharacter::get_name(){
  return name;
}

BaseCharacter::~BaseCharacter() {}
