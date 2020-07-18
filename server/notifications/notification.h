#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <vector>
class Notification {
 public:
  explicit Notification(std::vector<unsigned char> &notification);
  virtual ~Notification();
  std::vector<unsigned char> vector;

 private:
  
};

#endif
