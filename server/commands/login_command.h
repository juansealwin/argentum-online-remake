#ifndef LOGIN_COMMAND_H
#define LOGIN_COMMAND_H

#include "command.h"

class ArgentumGame;
// class Command; forward declaration x si llego a necesitar

class LoginCommand {//: public Command {
 public:
  LoginCommand(const unsigned int room_number);
  LoginCommand(const LoginCommand &) = delete;
  ~LoginCommand();
  // Ejecuta cambios en el juego segun
  //virtual void execute(ArgentumGame *game);

 private:
  const int room_number;
};

#endif
