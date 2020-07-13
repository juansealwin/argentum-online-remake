#include "buy_item_command_dto.h"

BuyItemCommandDTO::BuyItemCommandDTO(const int item) : item(item) {}

BuyItemCommandDTO::~BuyItemCommandDTO() {}

int BuyItemCommandDTO::get_id() { return BUY_ITEM_COMMAND; }
