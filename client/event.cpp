#include "event.h"

Event::Event(int id, request_t new_request)
    : id_player(id), request(new_request) {}

Event::Event(request_t new_request)
    : request(new_request) {}

Event::Event(int id)
    : id_player(id) {}

Event::Event(){}

Event::~Event() {}

void Event::set_request(request_t new_request){
  request = new_request;
}

bool Event::is_ending() { return (request == quit) ? true : false; }