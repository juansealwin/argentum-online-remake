#include "game_status_notification.h"

GameStatusNotification::GameStatusNotification(
    std::vector<unsigned char> &GameStatusNotification)
    : Notification(GameStatusNotification) {}

GameStatusNotification::~GameStatusNotification() {}