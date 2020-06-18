#include "defensive_item.h"

DefensiveItem::DefensiveItem(int id, unsigned int min_defense,
                             unsigned int max_defense)
    : Item(id), min_defense(min_defense), max_defense(max_defense) {}

DefensiveItem::~DefensiveItem() {}
