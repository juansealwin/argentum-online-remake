#include "use_item_command_dto.h"

UseItemCommandDTO::UseItemCommandDTO(const int slot, const bool equip)
    : item_slot(slot), equipped(equip) {}

UseItemCommandDTO::~UseItemCommandDTO() {}

int UseItemCommandDTO::get_id() { return USE_ITEM_COMMAND; }