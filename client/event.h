#ifndef EVENT_H
#define EVENT_H

typedef enum { quit = 0, move_down, move_up, move_left, move_right } request_t;

class Event {
 private:
  int id_player;
  request_t request;

 public:
  Event();
  Event(int, request_t);
  Event(request_t);
  Event(int);
  Event(Event&);
  ~Event();
  bool isEnding();
  void setRequest(request_t);
};

#endif