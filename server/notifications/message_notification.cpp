#include "message_notification.h"

MessageNotification::MessageNotification(std::vector<unsigned char> &message)
    : Notification(message) {}

MessageNotification::~MessageNotification() {}
