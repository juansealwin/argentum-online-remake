#ifndef BANK_ITEM_COMMAND_H
#define BANK_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class GetBankedItemsCommand : public Command {
 public:
  GetBankedItemsCommand(const unsigned int uid);
  GetBankedItemsCommand(const GetBankedItemsCommand &) = delete;
  ~GetBankedItemsCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);
};

#endif
