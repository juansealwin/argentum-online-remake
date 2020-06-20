#include "banker.h"
#include <iostream>
Banker::Banker(int x, int y, int type, char repr)
     : Entity(x, y, type, repr) {}

void Banker::update() {
  //std::cout << "Trying to update Banker, to be implemented" << std::endl;
}
Banker::~Banker() {}
