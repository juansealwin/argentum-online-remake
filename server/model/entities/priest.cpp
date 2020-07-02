#include "priest.h"
#include <iostream>
Priest::Priest(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr) {}

void Priest::update() {
  //std::cout << "Trying to update Priest, to be implemented" << std::endl;
}
Priest::~Priest() {}
