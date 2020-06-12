#include "monster.h"

Monster::Monster(int x, int y, int id, char repr) :
		BaseCharacter(x, y, id, repr) {
}

bool Monster::is_movable() {
	return true;
}

Monster::~Monster() {}
