#ifndef UNBANK_ITEM_COMMAND_H
#define UNBANK_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class UnbankItemCommand : public Command {
 public:
  UnbankItemCommand(const unsigned int uid, const int item);
  UnbankItemCommand(const UnbankItemCommand &) = delete;
  ~UnbankItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
};

#endif
