#include "unbank_gold_command_dto.h"

UnbankGoldCommandDTO::UnbankGoldCommandDTO(const int ammount) : ammount(ammount) {}

UnbankGoldCommandDTO::~UnbankGoldCommandDTO() {}

int UnbankGoldCommandDTO::get_id() { return UNBANK_GOLD_COMMAND; }