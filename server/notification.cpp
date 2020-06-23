#include "notification.h"

Notification::Notification(std::vector<unsigned char> &notification)
    : vector(notification) {}

Notification::~Notification() {}