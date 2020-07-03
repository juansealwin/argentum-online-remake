#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "command.h"
#include "argentum_game.h"
class ArgentumGame;
// class Command; forward declaration x si llego a necesitar

class AttackCommand : public Command {
 public:
  AttackCommand(const unsigned int uid);
  AttackCommand(const AttackCommand &) = delete;
  ~AttackCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
