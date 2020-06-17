#include "entity.h"
#include "stdint.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter : public Entity {
 public:
  // Este primer constructor lo usa la clase hija Monster
  BaseCharacter(int x, int y, int type, char repr, int max_hp, int level);
  // Este segundo constructor lo usa el heroe ya que max_hp en ese caso es
  // calculado
  BaseCharacter(int x, int y, int type, char repr, int level);
  // Este tercer constructor es temporal para los npcs (sacerdote, etc) ya que
  // no tienen nada que ver con los monstruos/heroes se puede borrar esto y hacer
  // que esos npcs hereden directamente de entidad
  BaseCharacter(int x, int y, int type, char repr);
  virtual ~BaseCharacter();
  BaseCharacter(const BaseCharacter &) = delete;

 protected:
  int max_hp;
  int level;
  int current_hp;
  int type;
  char representation;
};

#endif  // BASE_CHARACTER_H
