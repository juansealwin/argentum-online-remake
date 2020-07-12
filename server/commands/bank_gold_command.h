#ifndef BANK_GOLD_COMMAND_H
#define BANK_GOLD_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class BankGoldCommand : public Command {
 public:
  BankGoldCommand(const unsigned int uid, const int ammount);
  BankGoldCommand(const BankGoldCommand &) = delete;
  ~BankGoldCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int ammount;
};

#endif
