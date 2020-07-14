#ifndef USE_ITEM_SPECIAL_H
#define USE_ITEM_SPECIAL_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class UseItemSpecial : public Command {
 public:
  UseItemSpecial(const unsigned int uid);
  UseItemSpecial(const UseItemSpecial &) = delete;
  ~UseItemSpecial();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
