#include "consumable.h"

Consumable::Consumable(int id, unsigned int mana_regen, unsigned int hp_regen)
    : Item(id), mana_regen(mana_regen), hp_regen(hp_regen) {}

Consumable::~Consumable() {}

void Consumable::use(Hero *hero) {
  hero->current_hp += hp_regen;
  if (hero->current_hp >= (int)hero->max_hp) hero->current_hp = hero->max_hp;
  hero->current_mana += mana_regen;
  if (hero->current_mana >= hero->max_mana) hero->current_mana = hero->max_mana;
}
