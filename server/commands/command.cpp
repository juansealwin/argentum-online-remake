#include "command.h"

#include <iostream>
Command::Command() {}
Command::Command(const unsigned int uid) : uid(uid) {}
Command::~Command() {}