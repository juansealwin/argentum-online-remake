#include "bank_status_notification.h"

#include "close_connection_notification.h"

BankStatusNotification::BankStatusNotification(std::vector<unsigned char> &data) : Notification(data) {

}

BankStatusNotification::~BankStatusNotification() {

}