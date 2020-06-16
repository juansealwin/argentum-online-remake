#include "monster.h"

Monster::Monster(int x, int y, int id, char repr, int hp, int level, int dps)
    : BaseCharacter(x, y, id, repr, hp, level), dps(dps) {}

bool Monster::is_movable() { return true; }

Monster::~Monster() {}
