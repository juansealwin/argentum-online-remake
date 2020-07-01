#include "starting_info_notification.h"

StartingInfoNotification::StartingInfoNotification(
    std::vector<unsigned char> &starting_info)
    : Notification(starting_info) {}

StartingInfoNotification::~StartingInfoNotification() {}
