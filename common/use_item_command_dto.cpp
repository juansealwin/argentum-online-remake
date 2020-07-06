#include "use_item_command_dto.h"

UseItemCommandDTO::UseItemCommandDTO(const int slot) : item_slot(slot){}

UseItemCommandDTO::~UseItemCommandDTO() {}

int UseItemCommandDTO::get_id() { return USE_ITEM_COMMAND; }