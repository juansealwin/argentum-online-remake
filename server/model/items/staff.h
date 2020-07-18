#ifndef STAFF_H
#define STAFF_H
#include "weapon.h"
class Staff : public Weapon {
 public:
  // recibe hp_regen porque hay un staff que cura al jugador, aunque se
  // podria hacer por otro lado
  Staff(int id, unsigned int min_damage, unsigned int max_damage,
        unsigned int range, unsigned int mana_consumption,
        unsigned int hp_regen);
  virtual ~Staff();
  virtual bool can_be_used_by(Hero *hero);
  //No deberia llamarse a use() si can_be_used_by devolvio false
  virtual void use(Hero *hero) override;
  void attack_use(Hero *hero);
  void special_use(Hero *hero);
  Staff(const Staff &) = delete;

  unsigned int mana_consumption, hp_regen;
};
#endif  // STAFF_H
