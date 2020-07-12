#ifndef BANK_ITEM_COMMAND_H
#define BANK_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class BankItemCommand : public Command {
 public:
  BankItemCommand(const unsigned int uid, const int item);
  BankItemCommand(const BankItemCommand &) = delete;
  ~BankItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
};

#endif
