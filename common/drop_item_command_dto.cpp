#include "drop_item_command_dto.h"

DropItemCommandDTO::DropItemCommandDTO(const int item_id) : item_id(item_id) {}

DropItemCommandDTO::~DropItemCommandDTO() {}

int DropItemCommandDTO::get_id() { return DROP_ITEM_COMMAND; }