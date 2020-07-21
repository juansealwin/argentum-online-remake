#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL.h>

#include <vector>
#include <string>

#include "attack_command_dto.h"
#include "character.h"
#include "commands_blocking_queue.h"
#include "events_queue.h"
#include "exception_messages.h"
#include "interactive_box.h"
#include "move_command_dto.h"
#include "npc.h"
#include "pick_up_command_dto.h"
#include "playable_character.h"
#include "quit_command_dto.h"
#include "sdl_exception.h"
#include "texture.h"
#include "use_item_command_dto.h"
#include "change_game_room_dto.h"
#include "drop_item_command_dto.h"
#include "private_message_dto.h"
#include "bank_item_command_dto.h"
#include "bank_gold_command_dto.h"
#include "unbank_gold_command_dto.h"
#include "unbank_item_command_dto.h"
#include "get_banked_items_command_dto.h"
#include "buy_item_command_dto.h"
#include "sell_item_command_dto.h"
#include "meditate_command_dto.h"
#include "heal_command_dto.h"
#include "revive_command_dto.h"
#include "use_item_special_command_dto.h"

#define MAX_MSG_LENGTH 65
#define PRIVATE_MSG '@'
#define MSG_MEDITATE "/meditar"
#define MSG_REVIVE "/revivir"
#define MSG_HEAL "/curar"
#define MSG_DEPOSIT "/depositar "
#define MSG_WITHDRAW "/retirar "
#define MSG_LIST "/listar"
#define MSG_BUY "/comprar "
#define MSG_SELL "/vender "
#define MSG_TAKE "/tomar"
#define MSG_DROP "/tirar"
#define STR_TURTLE_SHIELD "escudo de tortuga"
#define STR_IRON_SHIELD "escudo de hierro"
#define STR_HOOD "capucha"
#define STR_IRON_HELMET "casco de hierro"
#define STR_MAGIC_HAT "sombrero magico"
#define STR_LEATHER_ARMOR "armadura de cuero"
#define STR_PLATE_ARMOR "armadura de plata"
#define STR_BLUE_TUNIC "tunica azul"
#define STR_HP_POTION "pocion de vida"
#define STR_MANA_POTION "pocion de mana"
#define STR_SWORD "espada"
#define STR_AXE "hacha"
#define STR_HAMMER "martillo"
#define STR_SIMPLE_BOW "arco simple"
#define STR_COMPOUND_BOW "arco compuesto"
#define STR_ASH_STICK "vara de fresno"
#define STR_GNARLED_STAFF "baculo nudoso"
#define STR_CRIMP_STAFF "baculo engarzado"
#define STR_ELVEN_ELUDE "laud elfico"
#define STR_DEADLY_STAFF "baculo mortifero"
#define WIDTH_RATIO_800 1
#define INV_ROWS_800x600 5
#define INV_COLS_800x600 4
#define SHOP_ROWS_800x600 4
#define SHOP_COLS_800x600 4


class EventHandler {
 private:
  CommandsBlockingQueue& commands_queue;
  EventsQueue& events_queue;
  bool& is_running;
  InteractiveBox inventory;
  InteractiveBox text_box;
  InteractiveBox shop_box;

 public:
  EventHandler(CommandsBlockingQueue& commands_queue, EventsQueue&, bool&);
  ~EventHandler();
  bool is_up();
  void get_events();
  void check_inpunt_send_command(std::string);
  item_t get_item_t(id_texture_t);
  item_t get_item_t(std::string);
};

#endif
