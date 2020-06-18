#include "hero.h"
Hero::Hero(int x, int y, int race_id, char repr, int level, int strength,
           int intelligence, int agility, int constitution, int f_class_hp,
           int f_race_hp, int f_race_recovery, int f_race_mana,
           int f_class_mana, int f_class_meditation, int gold, int class_id,
           Map *map)
    : BaseCharacter(x, y, race_id, repr, level, map),
      strength(strength),
      intelligence(intelligence),
      agility(agility),
      constitution(constitution),
      f_class_hp(f_class_hp),
      f_race_hp(f_race_hp),
      f_race_recovery(f_race_recovery),
      f_race_mana(f_race_mana),
      f_class_mana(f_class_mana),
      f_class_meditation(f_class_meditation),
      gold(gold),
      class_id(class_id) {
  max_hp = current_hp = constitution * f_class_hp * f_race_hp * level;
  max_mana = current_mana = intelligence * f_class_mana * f_race_mana * level;
}

void Hero::update() {
  // aumento de vida, mana, etc.
  // std::cout << "Updating hero: not implemented" << std::endl;
}

int Hero::damage(Hero *other) {  // deberia cambiarlo por un baseCharacter ya
                                 // que puedo atacar a monstruos
  int dmg = strength;            //+ sumar lo de los items
  // actualizar experiencia
  return other->receive_damage(dmg, false);
}
// devuelve el dano que efectivamente recibi
int Hero::receive_damage(int damage, bool critical) {
  int actual_damage = damage;
  if (critical)
    actual_damage *= CRITICAL_DAMAGE_MULTIPLIER;
  else {  // esquivar si rand(0,1) ** agilidad < 0.001
    // si no se pudo esquivar:
    // defensa = rand(armaduramin,armaduramax) + rand(cascomin,cascomas) +
    // rand(cascomin,cascomax)
    int defense = 0;
    actual_damage -= defense;
  }  // Hacer chequeos si esta vivo etc?
  return actual_damage;
}

Hero::~Hero() {}