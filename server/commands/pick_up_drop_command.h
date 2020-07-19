#ifndef PICK_UP_DROP_H
#define PICK_UP_DROP_H

#include "command.h"
#include "argentum_game.h"
class PickUpDropCommand : public Command {
 public:
  explicit PickUpDropCommand(const unsigned int uid);
  PickUpDropCommand(const PickUpDropCommand &) = delete;
  ~PickUpDropCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

};

#endif
