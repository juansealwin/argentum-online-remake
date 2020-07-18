#include "bank_item_command_dto.h"

BankItemCommandDTO::BankItemCommandDTO(const int item) : item(item) {}

BankItemCommandDTO::~BankItemCommandDTO() {}

int BankItemCommandDTO::get_id() { return BANK_ITEM_COMMAND; }