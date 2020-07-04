#include "monster.h"

#include <iostream>
Monster::Monster(unsigned int unique_id, int x, int y, int id, char repr,
                 int hp, int level, int dps, Map &map)
    : BaseCharacter(unique_id, x, y, id, repr, hp, level, map), dps(dps) {
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

  //-------- Movimiento -----------//
  int x_step = std::get<0>(moves.at(current_move));
  int y_step = std::get<1>(moves.at(current_move));
  current_move++;

  int next_x_pos = x_position + x_step;
  int next_y_pos = y_position + y_step;
  if (!map.tile_is_safe(next_x_pos, next_y_pos)) {
    move(next_x_pos, next_y_pos);
  }
  if (current_move >= moves.size()) current_move = 0;
}

unsigned int Monster::receive_damage(unsigned int damage, bool critical,
                                     unsigned int weapon_origin) {
  // std::cout << "Monster received damage!!" << std::endl;
  if (!alive) throw ModelException("Monster is already death!", "6");
  int last_hp = current_hp;
  current_hp = std::max(current_hp - (int)damage, 0);
  if (current_hp == 0) alive = false;
  // std::cout << "Monster is alive? " << alive << std::endl;
  // std::cout << "Returning" << last_hp - current_hp << std::endl;
  // std::cout << "last hp: " << last_hp << " current_hp " << current_hp
  //           << std::endl;
  std::cout << "Monster got affected by weapon!. is alive? " << alive;
  affected_by = weapon_origin;
  return last_hp - current_hp;
}

void Monster::notify_damage_done(BaseCharacter *other,
                                 unsigned int damage_done) {
  // subirlo de nivel?
}

bool Monster::is_death() { return !alive; }

Monster::~Monster() {}
