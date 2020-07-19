#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>

#include <string>

#include "interactive_box.h"
#include "text_box.h"
#include "texture.h"

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
#define X_PLAY_BUTTON 608
#define Y_PLAY_BUTTON 136
#define PLAY_BUTTON_W 100
#define PLAY_BUTTON_H 64
#define CHECKBOX_EDGE 24
#define WARNING_MESSAGE "Se permite un personaje por usuario."
#define WARNING_MESSAGE2 \
  "En caso de tener uno, jugará con el anteriormente creado."
#define MESSAGE_HUMAN "Son una raza equilibrada."
#define MESSAGE_ELF \
  "Son muy inteligentes y ágiles pero de una constitución física frágil."
#define MESSAGE_DWARF \
  "Son muy fuertes y resistentes, pero la agilidad no es lo suyo."
#define MESSAGE_GNOME \
  "Inteligentes y resistentes, pero mucho menos ágiles que los elfos."
#define MESSAGE_WARRIOR                                                    \
  "han dedicado toda su vida al combate, son típicamente más fuertes y " \
  "resistentes que otros pero carecen de la sabiduría para usar la magia."
#define MESSAGE_PALADIN                                                   \
  "Entrenados para el combate, son fuertes y resistentes aunque capaces " \
  "también de usar magia, con una mucho menor inteligencia que un mago."
#define MESSAGE_CLERIC                                                         \
  "Un poco menos inteligentes y hábiles que los magos, un clérigo compensa " \
  "sus falencias con un mayor desempeño físico."
#define MESSAGE_WIZARD                                                   \
  "Quienes hayan estudiado magia han cultivados sus mentes y menos sus " \
  "cuerpos."
#define RACE_HUMAN 25
#define RACE_ELF 26
#define RACE_DWARF 27
#define RACE_GNOME 28
#define CLASS_WARRIOR 24
#define CLASS_PALADIN 23
#define CLASS_CLERIC 21
#define CLASS_WIZARD 20

class Lobby {
 private:
  Texture* log_in;
  Texture* character_selection;
  Texture* check_mark;
  SDL_Renderer* renderer;
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
  InteractiveBox play;
  bool is_running;
  bool quit;
  std::string user_name;
  std::string pass;
  std::string pass_hidden;
  std::string race_message;
  std::string class_message;
  int race_selected;
  int class_selected;

 public:
  Lobby(SDL_Renderer*);
  ~Lobby();
  void start_lobby();
  void lobby_log_in();
  void lobby_character_selection();
};

#endif
