#include "item_factory.h"

Item *ItemFactory::create_random_item(Json::Value items_config) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  const int first_item_id = 1;
  const int last_item_id = 19;
  std::uniform_int_distribution<int> distribution(first_item_id, last_item_id);
  int random_id = distribution(generator);
  std::cout << "item id generated is " << random_id << std::endl;
  std::cout << "out of item random generator" << std::endl;
  std::cout << items_config["defense"] << std::endl;
  return nullptr;
}