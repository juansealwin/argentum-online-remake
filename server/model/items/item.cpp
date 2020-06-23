#include "hero.h"
#include "item.h"

Item::Item(int id) : id(id) {}

Item::~Item() {}

bool Item::can_be_used_by(Hero &hero) {
  return true;
}

void Item::self_apply(Hero &hero) {}