#include "sell_item_command_dto.h"

SellItemCommandDTO::SellItemCommandDTO(const int item) : item(item) {}

SellItemCommandDTO::~SellItemCommandDTO() {}

int SellItemCommandDTO::get_id() { return SELL_ITEM_COMMAND; }
