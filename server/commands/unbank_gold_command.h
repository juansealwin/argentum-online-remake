#ifndef UNBANK_GOLD_COMMAND_H
#define UNBANK_GOLD_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class UnbankGoldCommand : public Command {
 public:
  UnbankGoldCommand(const unsigned int uid, const int ammount);
  UnbankGoldCommand(const UnbankGoldCommand &) = delete;
  ~UnbankGoldCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int ammount;
};

#endif
