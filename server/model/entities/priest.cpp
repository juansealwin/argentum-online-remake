#include "priest.h"
#include <iostream>
Priest::Priest(unsigned int unique_id, int x, int y, int type, char repr)
     : Entity(unique_id, x, y, type, repr, orientation_down) {}

Priest::~Priest() {}
