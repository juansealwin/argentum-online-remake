#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "command.h"
class ArgentumGame;
// class Command; forward declaration x si llego a necesitar

class QuitCommand : public Command {
 public:
  QuitCommand();
  QuitCommand(const QuitCommand &) = delete;
  ~QuitCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);
};

#endif
