#ifndef USE_ITEM_COMMAND_H
#define USE_ITEM_COMMAND_H

#include "argentum_game.h"
#include "command.h"
// class Command; forward declaration x si llego a necesitar

class UseItemCommand : public Command {
 public:
  UseItemCommand(const unsigned int uid, const int item, const int slot,
                 const bool equipped);
  UseItemCommand(const UseItemCommand &) = delete;
  ~UseItemCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int item;
  int slot;
  bool equipped;
};

#endif
