#include "meditate_command.h"
#include <iostream>
MeditateCommand::MeditateCommand(const unsigned int uid) : Command(uid) {}

MeditateCommand::~MeditateCommand() {}

void MeditateCommand::execute(ArgentumGame *game) {
  game->hero_meditate(uid);
}
