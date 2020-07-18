#ifndef REVIVE_COMMAND_H
#define REVIVE_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class ReviveCommand : public Command {
 public:
  explicit ReviveCommand(const unsigned int uid);
  ReviveCommand(const ReviveCommand &) = delete;
  ~ReviveCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
