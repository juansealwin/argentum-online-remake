#include "use_item_command.h"

UseItemCommand::UseItemCommand(const unsigned int uid, const int item,
                               const int slot, const bool equipped)
    : Command(uid), item(item), slot(slot), equipped(equipped) {}

UseItemCommand::~UseItemCommand() {}

void UseItemCommand::execute(ArgentumGame *game) {
  std::cout << "executing use item command "
                  << "slot is: " << slot << " equipped is " << equipped
                  << " item is " << item << std::endl;
  if(equipped) {
    game->hero_dequip_item(uid, item);
  }
  else {
    std::cout << "item is not equipped" << std::endl;
  }
}