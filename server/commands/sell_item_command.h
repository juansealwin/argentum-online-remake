#ifndef SELL_ITEM_COMMAND_H
#define SELL_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class SellItemCommand : public Command {
 public:
  SellItemCommand(const unsigned int uid, const int item);
  SellItemCommand(const SellItemCommand &) = delete;
  ~SellItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
};

#endif
