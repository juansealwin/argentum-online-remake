#include "use_item_special_command_dto.h"

UseItemSpecialCommandDTO::UseItemSpecialCommandDTO() : CommandDTO() {}

UseItemSpecialCommandDTO::~UseItemSpecialCommandDTO() {}

bool UseItemSpecialCommandDTO::stops_run() { return false; }

int UseItemSpecialCommandDTO::get_id() { return USE_ITEM_SPECIAL_COMMAND; }
