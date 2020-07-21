#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>

#include <string>

#include "interactive_box.h"
#include "sound_effect.h"
#include "text_box.h"
#include "texture.h"

#define WIDTH_800 800
#define HEIGHT_600 600
#define WIDTH_1024 1024
#define HEIGHT_768 768
#define GRASS 0
#define DESERT 1
#define ARGAL 2
#define ICE 3

#define MAX_USER_INPUT 14
#define X_LOGIN 489
#define Y_LOGIN 425
#define X_INPUT 284
#define Y_USER_INPUT 430
#define Y_PASSWORD_INPUT 466
#define Y_RES 532
#define X_RES_800x600 350
#define X_RES_1024x768 537
#define X_RES_FS 718
#define X_RACE 195
#define Y_RACE_HUMAN 150
#define Y_RACE_ELF 215
#define Y_RACE_DWARF 289
#define Y_RACE_GNOME 360
#define X_CLASS 418
#define Y_CLASS_WARRIOR 151
#define Y_CLASS_PALADIN 216
#define Y_CLASS_CLERIC 288
#define Y_CLASS_WIZARD 364
#define X_PLAY_BUTTON 648
#define Y_PLAY_BUTTON 527
#define X_MAP 762
#define Y_MAP_GRASS 75
#define Y_MAP_DESERT 122
#define Y_MAP_ARGAL 168
#define Y_MAP_ICE 215
#define PLAY_BUTTON_W 122
#define PLAY_BUTTON_H 62
#define CHECKBOX_EDGE 24
#define WARNING_MESSAGE "Se permite un personaje por usuario."
#define WARNING_MESSAGE2 \
  "En caso de tener uno, jugara con el anteriormente creado."
#define MESSAGE_HUMAN "Son una raza equilibrada."
#define MESSAGE_ELF \
  "Son muy inteligentes y agiles pero de una constitucion fisica fragil."
#define MESSAGE_DWARF \
  "Son muy fuertes y resistentes, pero la agilidad no es lo suyo."
#define MESSAGE_GNOME \
  "Inteligentes y resistentes, pero mucho menos agiles que los elfos."
#define MESSAGE_WARRIOR \
  "Son los mas fuertes y resistentes, pero incapaces de usar magia."
#define MESSAGE_PALADIN \
  "Son fuertes y resistentes, y usuarios basicos de magia."
#define MESSAGE_CLERIC \
  "Muy inteligentes para usar magia y suplir debilidades fisicas "
#define MESSAGE_WIZARD \
  "Los mas podersos usuarios de magia, aunque debiles y fragiles"
#define RACE_HUMAN "human"
#define RACE_ELF "elf"
#define RACE_DWARF "dwarf"
#define RACE_GNOME "gnome"
#define CLASS_WARRIOR "warrior"
#define CLASS_PALADIN "paladin"
#define CLASS_CLERIC "cleric"
#define CLASS_WIZARD "mage"

class Lobby {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Texture* log_in;
  Texture* character_selection;
  Texture* check_mark;
  TextBox user_text_box;
  TextBox password_text_box;
  TextBox race_text_box;
  TextBox class_text_box;
  InteractiveBox user;
  InteractiveBox password;
  InteractiveBox resolution_800x600;
  InteractiveBox resolution_1024x768;
  InteractiveBox resolution_fs;
  InteractiveBox log;
  InteractiveBox option_human;
  InteractiveBox option_elf;
  InteractiveBox option_dwarf;
  InteractiveBox option_gnome;
  InteractiveBox option_warrior;
  InteractiveBox option_paladin;
  InteractiveBox option_cleric;
  InteractiveBox option_wizard;
  InteractiveBox option_grass_map;
  InteractiveBox option_desert_map;
  InteractiveBox option_argal_map;
  InteractiveBox option_ice_map;
  InteractiveBox play;
  bool is_running;
  bool quit;
  int screen_width;
  int screen_height;
  bool full_screen;
  std::string user_name;
  std::string pass;
  std::string pass_hidden;
  std::string race_message;
  std::string class_message;
  std::string race_selected;
  std::string class_selected;
  int initial_map;
  SoundEffect click_sound;
  SoundEffect lobby_music;

 public:
  Lobby(SDL_Window*, SDL_Renderer*);
  ~Lobby();
  bool start_lobby();
  void lobby_log_in();
  void lobby_character_selection();
  void check_mouse_click_login(int&, int&, int&, bool&, bool&);
  std::string get_user_name();
  std::string get_player_race();
  std::string get_player_class();
  int get_initial_map();
  int get_screen_width();
  int get_screen_height();
  bool get_fs_mode();
};

#endif
