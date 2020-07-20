#include "lobby.h"

Lobby::Lobby(SDL_Window* win, SDL_Renderer* ren)
    : window(win),
      renderer(ren),
      user_text_box(USER, ""),
      password_text_box(PASSWORD, ""),
      race_text_box(RACE_MSG, WARNING_MESSAGE),
      class_text_box(CLASS_MSG, WARNING_MESSAGE2) {
  log_in = new Texture("lobby.png", renderer);
  character_selection = new Texture("lobby2.png", renderer);
  check_mark = new Texture("tilde.png", renderer);
  is_running = true;
  quit = false;
  click_sound.set_sound("click.mp3");
  lobby_music.set_music("musica_lobby.mp3");

  // Parte del lobby de log in
  user = InteractiveBox(X_INPUT, Y_USER_INPUT, 182, 20);
  password = InteractiveBox(X_INPUT, Y_PASSWORD_INPUT, 182, 20);
  resolution_800x600 =
      InteractiveBox(X_RES_800x600, Y_RES, CHECKBOX_EDGE, CHECKBOX_EDGE);
  resolution_1024x768 =
      InteractiveBox(X_RES_1024x768, Y_RES, CHECKBOX_EDGE, CHECKBOX_EDGE);
  resolution_fs = InteractiveBox(X_RES_FS, Y_RES, CHECKBOX_EDGE, CHECKBOX_EDGE);
  log = InteractiveBox(X_LOGIN, Y_LOGIN, 92, 58);
  user_name = "";
  pass = "";
  pass_hidden = "";
  // Resolución predeterminada
  screen_width = WIDTH_800;
  screen_height = HEIGHT_600;
  full_screen = false;

  // Parte del lobby de character selection
  option_human =
      InteractiveBox(X_RACE, Y_RACE_HUMAN, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_elf = InteractiveBox(X_RACE, Y_RACE_ELF, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_dwarf =
      InteractiveBox(X_RACE, Y_RACE_DWARF, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_gnome =
      InteractiveBox(X_RACE, Y_RACE_GNOME, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_warrior =
      InteractiveBox(X_CLASS, Y_CLASS_WARRIOR, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_paladin =
      InteractiveBox(X_CLASS, Y_CLASS_PALADIN, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_cleric =
      InteractiveBox(X_CLASS, Y_CLASS_CLERIC, CHECKBOX_EDGE, CHECKBOX_EDGE);
  option_wizard =
      InteractiveBox(X_CLASS, Y_CLASS_WIZARD, CHECKBOX_EDGE, CHECKBOX_EDGE);
  play = InteractiveBox(X_PLAY_BUTTON, Y_PLAY_BUTTON, PLAY_BUTTON_W,
                        PLAY_BUTTON_H);
  race_message = WARNING_MESSAGE;
  class_message = WARNING_MESSAGE2;
  race_selected = RACE_HUMAN;
  class_selected = CLASS_WARRIOR;
}

Lobby::~Lobby() {
  delete log_in;
  delete character_selection;
  delete check_mark;
}

bool Lobby::start_lobby() {
  bool exit_success = true;
  lobby_music.play_music();
  lobby_music.decrease_music_volume(80);
  if (!quit) lobby_log_in();
  if (!quit) lobby_character_selection();
  lobby_music.stop_music();
  if (quit) exit_success = false;

  return exit_success;
}

void Lobby::lobby_log_in() {
  SDL_Event event;
  // resolución por default
  int x_check_mark = X_RES_800x600;
  bool get_user_text = false;
  bool get_password_text = false;
  int x, y;
  while (is_running) {
    while (SDL_PollEvent(&event) != 0) {
      // El usuario cierra la ventana
      if (event.type == SDL_QUIT) {
        quit = true;
        is_running = false;
        break;
      }

      // Eventos de mouse
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // int x, y;
        SDL_GetMouseState(&x, &y);
        check_mouse_click_login(x, y, x_check_mark, get_user_text,
                                get_password_text);
      }
      if (get_user_text && user.mouse_click_in(x, y)) {
        // get_user_text = true;
        get_password_text = false;
        SDL_Event event_chat;
        bool need_letter = true;

        // Se va a escribir hasta que se haga click fuera del campo 'usuario'
        while (need_letter && user.mouse_click_in(x, y)) {
          while (SDL_PollEvent(&event_chat) != 0) {
            // Chequea si se quiere cerrar en el medio de la escritura
            if (event_chat.type == SDL_QUIT) {
              quit = true;
              is_running = false;
              SDL_GetMouseState(&x, &y);
              break;
            }

            // Chequea si el click fue fuera de la caja de texto
            if (event_chat.type == SDL_MOUSEBUTTONDOWN) {
              SDL_GetMouseState(&x, &y);

              check_mouse_click_login(x, y, x_check_mark, get_user_text,
                                      get_password_text);
            }

            // Chequeamos si el usuario quiere borrar algo
            if (event_chat.type == SDL_KEYDOWN &&
                event_chat.key.keysym.sym == SDLK_BACKSPACE) {
              if (user_name.length()) {
                user_name.pop_back();
                need_letter = false;
              }
            }

            // Chequeamos si el usuario quiere escribir
            else if (event_chat.type == SDL_TEXTINPUT) {
              // Para impedir el copiado y pegado
              if (!(SDL_GetModState() & KMOD_CTRL &&
                    (event_chat.text.text[0] == 'c' ||
                     event_chat.text.text[0] == 'C' ||
                     event_chat.text.text[0] == 'v' ||
                     event_chat.text.text[0] == 'V'))) {
                if (user_name.length() < MAX_USER_INPUT) {
                  // Agregamos el caracter presionado
                  user_name += *event_chat.text.text;
                  need_letter = false;
                }
              }
            }
          }
        }

      } else if (get_password_text && password.mouse_click_in(x, y)) {
        get_password_text = true;
        get_user_text = false;
        SDL_Event event_input;
        bool need_letter = true;

        // Se va a escribir hasta que se haga click fuera del campo
        while (need_letter && password.mouse_click_in(x, y)) {
          while (SDL_PollEvent(&event_input) != 0) {
            // Chequea si se quiere cerrar en el medio de la escritura
            if (event_input.type == SDL_QUIT) {
              quit = true;
              is_running = false;
              SDL_GetMouseState(&x, &y);
              break;
            }

            // Chequea si el click fue fuera de la caja de texto
            if (event_input.type == SDL_MOUSEBUTTONDOWN) {
              SDL_GetMouseState(&x, &y);
              check_mouse_click_login(x, y, x_check_mark, get_user_text,
                                      get_password_text);
            }

            // Chequeamos si el usuario quiere borrar algo
            else if (event_input.type == SDL_KEYDOWN &&
                     event_input.key.keysym.sym == SDLK_BACKSPACE) {
              if (pass.length()) {
                pass.pop_back();
                pass_hidden.pop_back();
                need_letter = false;
              }
            }

            // Chequeamos si el usuario quiere escribir
            else if (event_input.type == SDL_TEXTINPUT) {
              // Para impedir el copiado y pegado
              if (!(SDL_GetModState() & KMOD_CTRL &&
                    (event_input.text.text[0] == 'c' ||
                     event_input.text.text[0] == 'C' ||
                     event_input.text.text[0] == 'v' ||
                     event_input.text.text[0] == 'V'))) {
                if (pass.length() < MAX_USER_INPUT) {
                  // Agregamos el caracter presionado
                  pass += *event_input.text.text;
                  pass_hidden += '*';
                  need_letter = false;
                }
              }
            }
          }
        }
      }

      // Limpiamos el render anterior
      SDL_RenderClear(renderer);

      // Seteamos los nuevos textos en los inputs
      user_text_box.set_text(user_name);
      user_text_box.set_texture(renderer);
      password_text_box.set_text(pass_hidden);
      password_text_box.set_texture(renderer);

      // Renderizamos el lobby actual
      log_in->render(renderer, NULL, 0, 0);

      // Creamos las texturas a partir de los nuevos textos
      user_text_box.render(renderer, 0, 0);
      password_text_box.render(renderer, 0, 0);

      // Renderizamos la opción de resolución
      check_mark->render(renderer, NULL, x_check_mark, Y_RES);

      // Renderizamos todo lo de esta pasada
      SDL_RenderPresent(renderer);
    }
  }
}

void Lobby::lobby_character_selection() {
  is_running = true;
  SDL_Event event;
  int x_race_checkmark;
  int y_race_checkmark;
  int x_class_checkmark;
  int y_class_checkmark;
  int x, y;
  bool race_checkmark = false;
  bool class_checkmark = false;

  while (is_running) {
    while (SDL_PollEvent(&event) != 0) {
      // El usuario cierra la ventana
      if (event.type == SDL_QUIT) {
        quit = true;
        is_running = false;
        break;
      }

      // Eventos de mouse
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // int x, y;
        SDL_GetMouseState(&x, &y);

        // Chequeamos si el usuario quiere alguna resolución en especial
        if (option_human.mouse_click_in(x, y)) {
          x_race_checkmark = X_RACE;
          y_race_checkmark = Y_RACE_HUMAN;
          race_selected = RACE_HUMAN;
          race_message = MESSAGE_HUMAN;
          race_checkmark = true;
          if (class_message == WARNING_MESSAGE2) class_message = "";
          click_sound.play_sound(0);
        } else if (option_elf.mouse_click_in(x, y)) {
          x_race_checkmark = X_RACE;
          y_race_checkmark = Y_RACE_ELF;
          race_selected = RACE_ELF;
          race_message = MESSAGE_ELF;
          race_checkmark = true;
          if (class_message == WARNING_MESSAGE2) class_message = "";
          click_sound.play_sound(0);
        } else if (option_dwarf.mouse_click_in(x, y)) {
          x_race_checkmark = X_RACE;
          y_race_checkmark = Y_RACE_DWARF;
          race_selected = RACE_DWARF;
          race_message = MESSAGE_DWARF;
          race_checkmark = true;
          if (class_message == WARNING_MESSAGE2) class_message = "";
          click_sound.play_sound(0);
        } else if (option_gnome.mouse_click_in(x, y)) {
          x_race_checkmark = X_RACE;
          y_race_checkmark = Y_RACE_GNOME;
          race_selected = RACE_GNOME;
          race_message = MESSAGE_GNOME;
          race_checkmark = true;
          if (class_message == WARNING_MESSAGE2) class_message = "";
          click_sound.play_sound(0);
        } else if (option_warrior.mouse_click_in(x, y)) {
          x_class_checkmark = X_CLASS;
          y_class_checkmark = Y_CLASS_WARRIOR;
          class_selected = CLASS_WARRIOR;
          class_message = MESSAGE_WARRIOR;
          class_checkmark = true;
          if (race_message == WARNING_MESSAGE) race_message = "";
          click_sound.play_sound(0);
        } else if (option_paladin.mouse_click_in(x, y)) {
          x_class_checkmark = X_CLASS;
          y_class_checkmark = Y_CLASS_PALADIN;
          class_selected = CLASS_PALADIN;
          class_message = MESSAGE_PALADIN;
          class_checkmark = true;
          if (race_message == WARNING_MESSAGE) race_message = "";
          click_sound.play_sound(0);
        } else if (option_cleric.mouse_click_in(x, y)) {
          x_class_checkmark = X_CLASS;
          y_class_checkmark = Y_CLASS_CLERIC;
          class_selected = CLASS_CLERIC;
          class_message = MESSAGE_CLERIC;
          class_checkmark = true;
          if (race_message == WARNING_MESSAGE) race_message = "";
          click_sound.play_sound(0);
        } else if (option_wizard.mouse_click_in(x, y)) {
          x_class_checkmark = X_CLASS;
          y_class_checkmark = Y_CLASS_WIZARD;
          class_selected = CLASS_WIZARD;
          class_message = MESSAGE_WIZARD;
          class_checkmark = true;
          if (race_message == WARNING_MESSAGE) race_message = "";
          click_sound.play_sound(0);
        } else if (play.mouse_click_in(x, y)) {
          is_running = false;
          click_sound.play_sound(0);
        }
      }

      // Limpiamos el render anterior
      SDL_RenderClear(renderer);

      // Seteamos los nuevos textos en los inputs
      race_text_box.set_text(race_message);
      race_text_box.set_texture(renderer);
      class_text_box.set_text(class_message);
      class_text_box.set_texture(renderer);

      // Renderizamos el lobby actual
      character_selection->render(renderer, NULL, 0, 0);

      // Creamos las texturas a partir de los nuevos textos
      race_text_box.render(renderer, 0, 0);
      class_text_box.render(renderer, 0, 0);

      // Renderizamos las opciones de raza y clase
      if (race_checkmark)
        check_mark->render(renderer, NULL, x_race_checkmark, y_race_checkmark);
      if (class_checkmark)
        check_mark->render(renderer, NULL, x_class_checkmark,
                           y_class_checkmark);

      // Renderizamos todo lo de esta pasada
      SDL_RenderPresent(renderer);
    }
  }
}

void Lobby::check_mouse_click_login(int& x, int& y, int& x_check_mark,
                                    bool& get_user_text,
                                    bool& get_password_text) {
  // Chequeamos si el mouse hizo click dentro del campo 'usuario'
  if (user.mouse_click_in(x, y)) {
    get_user_text = true;
    get_password_text = false;
    SDL_StartTextInput();
  }
  // Chequeamos si el mouse hizo click dentro del del campo 'contraseña'
  else if (password.mouse_click_in(x, y) || get_password_text) {
    get_user_text = false;
    get_password_text = true;
    SDL_StartTextInput();
  } else {
    get_user_text = false;
    get_password_text = false;
    SDL_StopTextInput();
  }

  // Chequeamos si el usuario quiere alguna resolución en especial
  if (resolution_800x600.mouse_click_in(x, y)) {
    x_check_mark = X_RES_800x600;
    screen_width = WIDTH_800;
    screen_height = HEIGHT_600;
    full_screen = false;
    click_sound.play_sound(0);

  } else if (resolution_1024x768.mouse_click_in(x, y)) {
    x_check_mark = X_RES_1024x768;
    screen_width = WIDTH_1024;
    screen_height = HEIGHT_768;
    full_screen = false;
    click_sound.play_sound(0);

  } else if (resolution_fs.mouse_click_in(x, y)) {
    x_check_mark = X_RES_FS;
    full_screen = true;
    click_sound.play_sound(0);

  } else if (log.mouse_click_in(x, y) && user_name != "") {
    is_running = false;
    click_sound.play_sound(0);
  }
}

std::string Lobby::get_user_name() { return user_name; }

std::string Lobby::get_player_race() { return race_selected; }

std::string Lobby::get_player_class() { return class_selected; }

int Lobby::get_screen_width() { return screen_width; }

int Lobby::get_screen_height() { return screen_height; }

bool Lobby::get_fs_mode() { return full_screen; }