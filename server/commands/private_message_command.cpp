
#include "private_message_command.h"

PrivateMessageCommand::PrivateMessageCommand(const unsigned int uid,
                                             const std::string &dst, const std::string &msg)
    : Command(uid), dst(dst), msg(msg) {}

PrivateMessageCommand::~PrivateMessageCommand() {}

void PrivateMessageCommand::execute(ArgentumGame *game) {
  game->send_message(uid ,dst, msg);
}