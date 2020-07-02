#include "banker.h"
#include <iostream>
Banker::Banker(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr) {}

void Banker::update() {
  //std::cout << "Trying to update Banker, to be implemented" << std::endl;
}
Banker::~Banker() {}
