#include "priest.h"
#include <iostream>
Priest::Priest(int x, int y, int type, char repr)
     : BaseCharacter(x, y, type, repr) {}

void Priest::update() {
  //std::cout << "Trying to update Priest, to be implemented" << std::endl;
}
Priest::~Priest() {}
