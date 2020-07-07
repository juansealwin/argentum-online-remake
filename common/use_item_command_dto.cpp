#include "use_item_command_dto.h"

UseItemCommandDTO::UseItemCommandDTO(const int it, const int slot,
                                     const bool equip)
    : item(it), item_slot(slot), equipped(equip) {}

UseItemCommandDTO::~UseItemCommandDTO() {}

int UseItemCommandDTO::get_id() { return USE_ITEM_COMMAND; }