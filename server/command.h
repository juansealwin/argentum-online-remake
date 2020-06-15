#ifndef COMMAND_H
#define COMMAND_H

#include "argentum_game.h"
class ArgentumGame; // por dependencia circular

class Command {
 public:
  Command();
  virtual ~Command();
  // Ejecuta cambios en el juego segun 
  virtual void execute(ArgentumGame *game) = 0;
};
#endif
