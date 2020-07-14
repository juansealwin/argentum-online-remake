#ifndef MEDITATE_COMMAND_H
#define MEDITATE_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class MeditateCommand : public Command {
 public:
  MeditateCommand(const unsigned int uid);
  MeditateCommand(const MeditateCommand &) = delete;
  ~MeditateCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
