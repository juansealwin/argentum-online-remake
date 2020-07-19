#ifndef GET_BANKED_ITEMS_COMMAND_H
#define GET_BANKED_ITEMS_COMMAND_H

#include "argentum_game.h"
#include "command.h"
//TO DO: Renombrar a esta clase, tambien se usa para
//obtener informacion de lo que venda un npc
class GetBankedItemsCommand : public Command {
 public:
  explicit GetBankedItemsCommand(const unsigned int uid);
  GetBankedItemsCommand(const GetBankedItemsCommand &) = delete;
  ~GetBankedItemsCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);
};

#endif
