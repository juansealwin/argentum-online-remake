#ifndef LOBBY_H
#define LOBBY_H

#include <SDL2/SDL.h>
#include <string>
#include "texture.h"
#include "interactive_box.h"
#include "text_box.h"

#define MAX_USER_INPUT 16
#define Y_CHECK_MARK_LOBBY_1 532
#define X_RES_800x600 350
#define X_RES_1024x768 537
#define X_RES_FS 718

class Lobby {
 private:
  Texture* log_in;
  Texture* character_selection;
  Texture* check_mark;
  SDL_Renderer* renderer;
  TextBox user_text_box;
  TextBox password_text_box;
  InteractiveBox user;
  InteractiveBox password;
  InteractiveBox resolution_800x600;
  InteractiveBox resolution_1024x768;
  InteractiveBox resolution_fs;
  InteractiveBox log;
  bool is_running;
  std::string user_name;
  std::string pass;
  std::string pass_hidden;

 public:
  Lobby(SDL_Renderer*);
  ~Lobby();
  void start_lobby();
};

#endif
