#ifndef BANK_STATUS_NOTIFICATION_H
#define BANK_STATUS_NOTIFICATION_H
#include "notification.h"
class BankStatusNotification : public Notification {
  // no cambia nada de la notificacion original, capaz no es necesaria, ver mas
  // adelante
 public:
  explicit BankStatusNotification(std::vector<unsigned char> &data);
  virtual ~BankStatusNotification();
};

#endif
