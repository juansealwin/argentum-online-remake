#ifndef BUY_ITEM_COMMAND_H
#define BUY_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class BuyItemCommand : public Command {
 public:
  BuyItemCommand(const unsigned int uid, const int item);
  BuyItemCommand(const BuyItemCommand &) = delete;
  ~BuyItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
};

#endif
