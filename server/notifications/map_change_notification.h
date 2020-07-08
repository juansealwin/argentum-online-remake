#ifndef MAP_CHANGE_NOTIFICATION_H
#define MAP_CHANGE_NOTIFICATION_H
#include "notification.h"
class MapChangeNotification : public Notification {
 public:
  MapChangeNotification(std::vector<unsigned char> &starting_info);
  virtual ~MapChangeNotification();
};

#endif
