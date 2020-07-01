#ifndef STARTING_INFO_NOTIFICATION_H
#define STARTING_INFO_NOTIFICATION_H
#include "notification.h"
class StartingInfoNotification : public Notification {
 public:
  StartingInfoNotification(std::vector<unsigned char> &starting_info);
  virtual ~StartingInfoNotification();
};

#endif
