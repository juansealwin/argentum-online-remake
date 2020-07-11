#ifndef PRIVATE_MESSAGE_COMMAND_H
#define PRIVATE_MESSAGE_COMMAND_H

#include "argentum_game.h"
#include "command.h"
class PrivateMessageCommand : public Command {
 public:
  PrivateMessageCommand(const unsigned int uid, std::string dst,
                        std::string msg);
  PrivateMessageCommand(const PrivateMessageCommand &) = delete;
  ~PrivateMessageCommand();
  // Ejecuta cambios en el juego segun
  virtual void execute(ArgentumGame *game);

 private:
  std::string dst;
  std::string msg;
};

#endif
