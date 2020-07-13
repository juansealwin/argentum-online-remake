#include "sale_info_notification.h"

SaleInfoNotification::SaleInfoNotification(std::vector<unsigned char> &message)
    : Notification(message) {}

SaleInfoNotification::~SaleInfoNotification() {}
