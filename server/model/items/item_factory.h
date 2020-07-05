#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H
#include "item.h"
#include <random>
#include <chrono>
namespace ItemFactory {
  Item *create_random_item(Json::Value items_config);
}
#endif  // ITEM_FACTORY_H
