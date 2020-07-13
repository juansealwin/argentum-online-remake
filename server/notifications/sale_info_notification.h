#ifndef SALE_INFO_NOTIFICATION_H
#define SALE_INFO_NOTIFICATION_H
#include "notification.h"
class SaleInfoNotification : public Notification {
  // no cambia nada de la notificacion original, capaz no es necesaria, ver mas
  // adelante
 public:
  SaleInfoNotification(std::vector<unsigned char> &data);
  virtual ~SaleInfoNotification();
};

#endif
