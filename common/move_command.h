#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "command.h"
class ArgentumGame;
// class Command; forward declaration x si llego a necesitar

class MoveCommand : public Command {
 public:
  MoveCommand(const int entity_id, const int next_x, const int next_y);
  MoveCommand(const MoveCommand &) = delete;
  ~MoveCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  int entity_id;
  int next_x;
  int next_y;
};

#endif
