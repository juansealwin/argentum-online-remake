#ifndef MONSTER_H
#define MONSTER_H
#include <vector>

#include "base_character.h"
#include "stdint.h"
class Monster : public BaseCharacter {
 public:
  Monster(unsigned int unique_id, int x, int y, int id, char repr, int hp,
          int level, int dps, Map *map);
  Monster(const Monster &) = delete;
  // Moverse si no hay enemigos cercanos (O si hay muy cerca acercarse a ellos)
  // Atacar si hay enemigo cercano (crear proyectil)
  void auto_move();
  virtual ~Monster();
  virtual unsigned int receive_damage(unsigned int damage, bool critical,
                                      unsigned int weapon_origin) override;
  virtual bool is_death() override;
  virtual void notify_damage_done(BaseCharacter *other,
                                  unsigned int damage_done) override;

 private:
  int dps;
  std::vector<std::tuple<int, int>> moves;
  std::size_t current_move = 0;
};

#endif  // MONSTER_H
