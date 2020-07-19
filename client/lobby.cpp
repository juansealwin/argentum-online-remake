#include "lobby.h"

Lobby::Lobby(SDL_Renderer* ren)
    : renderer(ren),
      user_text_box(USER, " "),
      password_text_box(PASSWORD, " ") {
  log_in = new Texture("lobby.png", renderer);
  character_selection = new Texture("lobby.png", renderer);
  check_mark = new Texture("tilde.png", renderer);
  is_running = true;
  user = InteractiveBox(284, 430, 182, 20);
  password = InteractiveBox(284, 466, 182, 20);
  resolution_800x600 = InteractiveBox(350, 533, 21, 21);
  resolution_1024x768 = InteractiveBox(537, 533, 21, 21);
  resolution_fs = InteractiveBox(718, 533, 21, 21);
  log = InteractiveBox(489, 425, 92, 58);
  user_name = "";
  pass = "";
  pass_hidden = "";
}

Lobby::~Lobby() {
  delete log_in;
  delete character_selection;
  delete check_mark;
}

void Lobby::start_lobby() {
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
        is_running = false;
        break;
      }

      // Eventos de mouse
      else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // int x, y;
        SDL_GetMouseState(&x, &y);

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
        }

        // Chequeamos si el usuario quiere alguna resolución en especial
        else if (resolution_800x600.mouse_click_in(x, y)) {
          x_check_mark = X_RES_800x600;
          get_user_text = false;
          get_password_text = false;

        } else if (resolution_1024x768.mouse_click_in(x, y)) {
          x_check_mark = X_RES_1024x768;
          get_user_text = false;
          get_password_text = false;

        } else if (resolution_fs.mouse_click_in(x, y)) {
          x_check_mark = X_RES_FS;
          get_user_text = false;
          get_password_text = false;

        } else if (log.mouse_click_in(x, y)) {
        } else {
          get_user_text = false;
          get_password_text = false;
        }

      } else if (get_user_text /*&& user.mouse_click_in(x, y)*/) {
        // get_user_text = true;
        get_password_text = false;
        SDL_Event event_chat;
        bool need_letter = true;

        // Se va a escribir hasta que se haga click fuera del campo 'usuario'
        while (need_letter && user.mouse_click_in(x, y)) {
          while (SDL_PollEvent(&event_chat) != 0) {
            // Chequea si el click fue fuera de la caja de texto*/
            if (event_chat.type == SDL_MOUSEBUTTONDOWN) {
              SDL_GetMouseState(&x, &y);
              if (!user.mouse_click_in(x, y)) get_user_text = false;
              SDL_StopTextInput();
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
                  std::cout << user_name << std::endl;
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
            // Chequea si el click fue fuera de la caja de texto
            if (event_input.type == SDL_MOUSEBUTTONDOWN) {
              SDL_GetMouseState(&x, &y);
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
                  std::cout << pass << std::endl;
                  need_letter = false;
                }
              }
            }
          }
        }
      }

      // Limpiamos el render anterior
      SDL_RenderClear(renderer);
      std::cout << "TEXTO: " << user_name << std::endl;
      std::cout << "PASS: " << pass << std::endl;
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
      check_mark->render(renderer, NULL, x_check_mark, Y_CHECK_MARK_LOBBY_1);

      // Renderizamos todo lo de esta pasada
      SDL_RenderPresent(renderer);
    }
  }
}