#ifndef DROP_ITEM_COMMAND_H
#define DROP_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class DropItemCommand : public Command {
 public:
  DropItemCommand(const unsigned int uid, const int item);
  DropItemCommand(const DropItemCommand &) = delete;
  ~DropItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
};

#endif
