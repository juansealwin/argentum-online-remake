#ifndef GAME_STATUS_NOTIFICATION_H
#define GAME_STATUS_NOTIFICATION_H
#include "notification.h"
class GameStatusNotification : public Notification {
  // no cambia nada de la notificacion original, capaz no es necesaria, ver mas
  // adelante
 public:
  explicit GameStatusNotification(std::vector<unsigned char> &GameStatusNotification);
  virtual ~GameStatusNotification();
};

#endif
