#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL.h>

#include <vector>

#include "character.h"
#include "commands_blocking_queue.h"
#include "exception_messages.h"
#include "move_command_dto.h"
#include "npc.h"
#include "playable_character.h"
#include "sdl_exception.h"
#include "texture.h"

class EventHandler {
 private:
  const int player_id;
  CommandsBlockingQueue& commands_queue;
  bool is_running = true;

 public:
  EventHandler(const int player_id, CommandsBlockingQueue& commands_queue);
  ~EventHandler();
  bool is_up();
  void get_events();
};

#endif
