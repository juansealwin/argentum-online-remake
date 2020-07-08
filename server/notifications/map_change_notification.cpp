#include "map_change_notification.h"

MapChangeNotification::MapChangeNotification(
    std::vector<unsigned char> &starting_info)
    : Notification(starting_info) {}

MapChangeNotification::~MapChangeNotification() {}
