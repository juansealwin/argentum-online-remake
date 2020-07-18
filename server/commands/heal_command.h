#ifndef HEAL_COMMAND_H
#define HEAL_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class HealCommand : public Command {
 public:
  explicit HealCommand(const unsigned int uid);
  HealCommand(const HealCommand &) = delete;
  ~HealCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
