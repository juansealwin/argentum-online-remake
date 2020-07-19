#ifndef MESSAGE_NOTIFICATION_H
#define MESSAGE_NOTIFICATION_H
#include "notification.h"
class MessageNotification : public Notification {
 public:
  explicit MessageNotification(std::vector<unsigned char> &message);
  virtual ~MessageNotification();
};

#endif
