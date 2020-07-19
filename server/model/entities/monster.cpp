#include "monster.h"

#include <iostream>
Monster::Monster(unsigned int unique_id, int x, int y, int id, char repr,
                 int hp, int level, int dps, Map *map, const std::string &name,
                 const float critical_damage_multiplier)
    : BaseCharacter(unique_id, x, y, id, repr, hp, level, map, name),
      dps(dps),
      critical_damage_multiplier(critical_damage_multiplier) {
  std::tuple<int, int> first_move = std::tuple<int, int>(0, 1);
  std::tuple<int, int> second_move = std::tuple<int, int>(1, 0);
  std::tuple<int, int> third_move = std::tuple<int, int>(0, -1);
  std::tuple<int, int> fourth_move = std::tuple<int, int>(-1, 0);
  moves.push_back(first_move);
  moves.push_back(second_move);
  moves.push_back(third_move);
  moves.push_back(fourth_move);
}

void Monster::auto_move() {
  if (!alive) return;
  int x_step = std::get<0>(moves.at(current_move));
  int y_step = std::get<1>(moves.at(current_move));
  current_move++;

  int next_x_pos = x_position + x_step;
  int next_y_pos = y_position + y_step;
  try_to_move_to_position(next_x_pos, next_y_pos);
  if (current_move >= moves.size()) current_move = 0;
}

void Monster::try_to_move_to_position(int x, int y) {
  if (!map->tile_is_safe(x, y)) {
    move(x, y);
  }
}

unsigned int Monster::receive_damage(unsigned int damage, bool critical,
                                     unsigned int weapon_origin) {
  if (!alive) throw ModelException("El monstruo ya ha muerto!");
  int last_hp = current_hp;
  int actual_damage = damage;
  if (critical) {
    actual_damage *= critical_damage_multiplier;
  }
  current_hp = std::max(current_hp - actual_damage, 0);
  if (current_hp == 0) alive = false;
  affected_by = weapon_origin;
  return last_hp - current_hp;
}

const Attack Monster::attack() {
  // Usar id de sword de la CFG
  Attack attack = {dps, false, 11, 0};
  return std::move(attack);
}

bool Monster::is_next_to(int other_x, int other_y) {
  return (HelperFunctions::distance(other_x, x_position, other_y, y_position) ==
          1);
}

bool Monster::is_close_to(int other_x, int other_y) {
  return (HelperFunctions::distance(other_x, x_position, other_y, y_position) <=
          5);
}

void Monster::move_closer_to(int other_x, int other_y) {
  using namespace std;
  vector<tuple<int, int>> possible_moves = get_possible_next_moves();
  tuple<int, int> best_move = possible_moves.at(0);
  int best_distance = HelperFunctions::distance(other_x, get<0>(best_move),
                                                other_y, get<1>(best_move));
  for (unsigned int j = 1; j < possible_moves.size(); j++) {
    int curr_x = get<0>(possible_moves.at(j));
    int curr_y = get<1>(possible_moves.at(j));
    int current_distance =
        HelperFunctions::distance(other_x, curr_x, other_y, curr_y);
    if (current_distance < best_distance) {
      best_move = possible_moves.at(j);
      best_distance = current_distance;
    }
  }
  int x = get<0>(best_move);
  int y = get<1>(best_move);
  try_to_move_to_position(x, y);
}

std::vector<std::tuple<int, int>> Monster::get_possible_next_moves() {
  using namespace std;
  // solo es posible moverse un casillero
  return {tuple<int, int>(x_position + 1, y_position),
          tuple<int, int>(x_position - 1, y_position),
          tuple<int, int>(x_position, y_position + 1),
          tuple<int, int>(x_position, y_position - 1)};
}

void Monster::notify_damage_done(BaseCharacter *other,
                                 unsigned int damage_done) {
  if (damage_done == 0) return;
  dps += other->level / damage_done;
}

bool Monster::is_death() { return !alive; }

Monster::~Monster() {}
