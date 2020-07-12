#include "bank_gold_command_dto.h"

BankGoldCommandDTO::BankGoldCommandDTO(const int ammount) : ammount(ammount) {}

BankGoldCommandDTO::~BankGoldCommandDTO() {}

int BankGoldCommandDTO::get_id() { return BANK_GOLD_COMMAND; }