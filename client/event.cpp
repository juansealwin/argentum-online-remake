#include "event.h"

Event::Event(int id, request_t new_request)
    : id_player(id), request(new_request) {}

Event::Event(request_t new_request)
    : request(new_request) {}

Event::Event(int id)
    : id_player(id) {}

Event::Event(){}

Event::~Event() {}

Event::Event(Event& other) {
  id_player = other.id_player;
  request = other.request;
}

void Event::setRequest(request_t new_request){
  request = new_request;
}

bool Event::isEnding() { return (request == quit) ? true : false; }