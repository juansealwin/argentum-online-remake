#include "unbank_item_command_dto.h"

UnbankItemCommandDTO::UnbankItemCommandDTO(const int item) : item(item) {}

UnbankItemCommandDTO::~UnbankItemCommandDTO() {}

int UnbankItemCommandDTO::get_id() { return UNBANK_ITEM_COMMAND; }