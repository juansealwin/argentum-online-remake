#ifndef CLOSE_CONNECTION_NOTIFICATION_H
#define CLOSE_CONNECTION_NOTIFICATION_H
#include "notification.h"
class CloseConnectionNotification : public Notification {
  // no cambia nada de la notificacion original, capaz no es necesaria, ver mas
  // adelante
 public:
  explicit CloseConnectionNotification(std::vector<unsigned char> &data);
  virtual ~CloseConnectionNotification();
};

#endif
