#include "item.h"

Item::Item(unsigned int id) : id(id) {}

Item::~Item() {}

bool Item::can_be_used_by(Hero *hero) {
  return true;
}