#ifndef USE_ITEM_SPECIAL_H
#define USE_ITEM_SPECIAL_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class UseItemSpecialCommand : public Command {
 public:
  UseItemSpecialCommand(const unsigned int uid);
  UseItemSpecialCommand(const UseItemSpecialCommand &) = delete;
  ~UseItemSpecialCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
