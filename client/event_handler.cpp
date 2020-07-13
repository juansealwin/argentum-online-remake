#include "event_handler.h"

EventHandler::~EventHandler() {}

EventHandler::EventHandler(CommandsBlockingQueue& commands_queue,
                           EventsQueue& queue, bool& run)
    : commands_queue(commands_queue), events_queue(queue), is_running(run) {
  // Seteamos las dimensiones de la "caja" de inventario
  inventory = InteractiveBox(640, 168, 139, 183);
  // Seteamos las dimensiones de la "caja" para escribir en el minichat
  text_box = InteractiveBox(10, 112, 544, 20);
}

void EventHandler::get_events() {
  try {
    background_music.set_music("musica_lobby.mp3");
    background_music.play_music();
    background_music.decrease_music_volume(90);
    SDL_Event event;
    while (is_running) {
      while (SDL_PollEvent(&event) != 0) {
        // El usuario cierra la ventana
        if (event.type == SDL_QUIT) {
          is_running = false;
          QuitCommandDTO* quit_command = new QuitCommandDTO();
          commands_queue.push(quit_command);

          // Aviso al renderer que hay que cerrar
          events_queue.push(EVENT_QUIT);
          break;
        }

        // Eventos de tecla presionada
        else if (event.type == SDL_KEYDOWN) {
          // Dependiendo que tecla presiona cambia el evento que sucede
          if (event.key.keysym.sym == SDLK_UP) {
            MoveCommandDTO* move_command = new MoveCommandDTO(move_up);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_DOWN) {
            MoveCommandDTO* move_command = new MoveCommandDTO(move_down);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_LEFT) {
            MoveCommandDTO* move_command = new MoveCommandDTO(move_left);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_RIGHT) {
            MoveCommandDTO* move_command = new MoveCommandDTO(move_right);
            commands_queue.push(move_command);
          }
          if (event.key.keysym.sym == SDLK_EQUALS) {
            background_music.increase_music_volume();
          }
          if (event.key.keysym.sym == SDLK_MINUS) {
            background_music.decrease_music_volume();
          }
          if (event.key.keysym.sym == SDLK_m) {
            background_music.stop_music();
          }
          if (event.key.keysym.sym == SDLK_p) {
            background_music.play_music();
          }
          if (event.key.keysym.sym == SDLK_SPACE) {
            AttackCommandDTO* attack_command = new AttackCommandDTO();
            commands_queue.push(attack_command);
          }
          if (event.key.keysym.sym == SDLK_a) {
            PickUpCommandDTO* pick_up_item_command = new PickUpCommandDTO();
            commands_queue.push(pick_up_item_command);
          }
          if (event.key.keysym.sym == SDLK_h) {
            DropItemCommandDTO* change_game_room_command =
                new DropItemCommandDTO(6);
            commands_queue.push(change_game_room_command);
          }

          if (event.key.keysym.sym == SDLK_1) {
            ChangeGameRoomDTO* change_game_room_command =
                new ChangeGameRoomDTO(1);
            commands_queue.push(change_game_room_command);
          }
          if (event.key.keysym.sym == SDLK_2) {
            ChangeGameRoomDTO* change_game_room_command =
                new ChangeGameRoomDTO(2);
            commands_queue.push(change_game_room_command);
          }
          if (event.key.keysym.sym == SDLK_3) {
            PrivateMessageDTO* private_message_command =
                new PrivateMessageDTO("test", "hello");
            commands_queue.push(private_message_command);
          }
          if (event.key.keysym.sym == SDLK_4) {
            std::cout << "creating bank item dto" << std::endl;
            BankItemCommandDTO* bank_item_command = new BankItemCommandDTO(6);
            commands_queue.push(bank_item_command);
          }
          if (event.key.keysym.sym == SDLK_5) {
            UnbankItemCommandDTO* bank_item_command =
                new UnbankItemCommandDTO(6);
            commands_queue.push(bank_item_command);
          }
          if (event.key.keysym.sym == SDLK_6) {
            BankGoldCommandDTO* bank_item_command = new BankGoldCommandDTO(6);
            commands_queue.push(bank_item_command);
          }
          if (event.key.keysym.sym == SDLK_7) {
            UnbankGoldCommandDTO* bank_item_command =
                new UnbankGoldCommandDTO(6);
            commands_queue.push(bank_item_command);
          }
          if (event.key.keysym.sym == SDLK_8) {
            GetBankedItemsCommandDTO* bank_item_command =
                new GetBankedItemsCommandDTO();
            commands_queue.push(bank_item_command);
          }
        }

        // Eventos de mouse
        // Eventos sobre el inventario
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
          int x, y;
          SDL_GetMouseState(&x, &y);

          // Chequeamos si el mouse hizo click dentro del inventario
          if (inventory.mouse_click_in(x, y)) {
            // Chequeamos que parte del inventario se clickeo
            int item_slot = inventory.get_item_clicked(x, y);
            bool is_equipped = false;
            id_texture_t item;
            // Chequeamos si hay item en el slot y si ademas esta equipado o no
            if (events_queue.push(EVENT_SELECT_ITEM, item, item_slot,
                                  is_equipped)) {
              UseItemCommandDTO* use_item_command = new UseItemCommandDTO(
                  get_item_t(item), item_slot, is_equipped);
              commands_queue.push(use_item_command);
            }
          }

          // Eventos sobre la caja de chat
          // Chequeamos si el mouse hizo click dentro de la caja de texto
          else if (text_box.mouse_click_in(x, y)) {
            SDL_Event event_chat;
            int msg_length = 0;
            // Se va a escribir hasta que se haga click fuera de text_box
            while (text_box.mouse_click_in(x, y)) {
              while (SDL_PollEvent(&event_chat) != 0) {
                // Chequea si el click fue fuera de la caja de texto
                if (event_chat.type == SDL_MOUSEBUTTONDOWN) {
                  SDL_GetMouseState(&x, &y);
                }

                // Chequeamos si el usuario quiere borrar algo
                else if (event_chat.type == SDL_KEYDOWN &&
                         event_chat.key.keysym.sym == SDLK_BACKSPACE) {
                  if (msg_length) {
                    msg_length = events_queue.delete_character();
                    events_queue.push(EVENT_MESSAGE);
                  }
                }

                // Chequeamos si el usuario apreto "enter" para enviar mensaje
                else if (event_chat.type == SDL_KEYDOWN &&
                         event_chat.key.keysym.sym == SDLK_RETURN) {
                  if (msg_length) {
                    check_inpunt_send_command(events_queue.flush_message());
                    msg_length = 0;
                    events_queue.push(EVENT_MESSAGE);
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
                    if (msg_length < MAX_MSG_LENGTH) {
                      // Agregamos el caracter presionado
                      msg_length =
                          events_queue.append_character(*event_chat.text.text);
                      events_queue.push(EVENT_MESSAGE);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void EventHandler::check_inpunt_send_command(std::string input_text) {
  // Chequeamos si el usuario quiere meditar
  if (input_text.compare(0, input_text.length(), MSG_MEDITATE) == 0) {
    std::cout << "COMANDO MEDITAR" << std::endl;
  }
  // Chequeamos si el usuario quiere curarse
  else if (input_text.compare(0, input_text.length(), MSG_HEAL) == 0) {
    std::cout << "COMANDO CURAR" << std::endl;
  }
  // Chequeamos si el usuario quiere depositar algún item en el banco
  else if (input_text.compare(0, strlen(MSG_DEPOSIT), MSG_DEPOSIT) == 0) {
    std::cout << "COMANDO DESPOSITAR" << std::endl;
    std::string item = input_text;
    std::string deposit = input_text.erase(0, strlen(MSG_DEPOSIT));
    int i = 0;

    // Chequeo si se quiere depositar oro o un item
    if (std::isdigit(deposit[i])) {
      for (i = 1; i < deposit.size(); i++) {
        if (!std::isdigit(deposit[i])) {
          break;
        }
      }
      // Si todos los caracteres fueron numeros se intenta depositar el oro
      if (i == deposit.size()) {
        BankGoldCommandDTO* bank_item_command =
            new BankGoldCommandDTO(std::stoi(deposit));
        commands_queue.push(bank_item_command);
      }
    } else {
      BankItemCommandDTO* bank_item_command = new BankItemCommandDTO(6);
            commands_queue.push(bank_item_command);
    }
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, strlen(MSG_WITHDRAW), MSG_WITHDRAW) == 0) {
    std::cout << "COMANDO RETIRAR" << std::endl;
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, input_text.length(), MSG_LIST) == 0) {
    std::cout << "COMANDO LISTAR" << std::endl;
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, strlen(MSG_BUY), MSG_BUY) == 0) {
    std::cout << "COMANDO COMPRAR" << std::endl;
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, strlen(MSG_SELL), MSG_SELL) == 0) {
    std::cout << "COMANDO VENDER" << std::endl;
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, input_text.length(), MSG_TAKE) == 0) {
    std::cout << "COMANDO TOMAR" << std::endl;
  }
  // Chequeamos si el usuario quiere retirar algún item del banco
  else if (input_text.compare(0, input_text.length(), MSG_DROP) == 0) {
    std::cout << "COMANDO TIRAR" << std::endl;
  }
  // Chequeamos si se ingreso un mensaje privado
  else if (input_text[0] == PRIVATE_MSG) {
    size_t pos = input_text.find(" ");
    std::string receiver = input_text.substr(1, pos - 1);
    std::string message = input_text.substr(pos + 1);

    PrivateMessageDTO* private_message_command =
        new PrivateMessageDTO(receiver, message);
    commands_queue.push(private_message_command);
  }
  // En otro caso es un comando inválido
  else {
    std::cout << "COMANDO INVALIDO" << std::endl;
  }
}

bool EventHandler::is_up() { return is_running; }

item_t EventHandler::get_item_t(id_texture_t texture) {
  item_t item;

  switch (texture) {
    case ID_TURTLE_SHIELD:
      item = TURTLE_SHIELD;
      break;

    case ID_IRON_SHIELD:
      item = IRON_SHIELD;
      break;

    case ID_HOOD:
      item = HOOD;
      break;

    case ID_IRON_HELMET:
      item = IRON_HELMET;
      break;

    case ID_MAGIC_HAT:
      item = MAGIC_HAT;
      break;

    case ID_LEATHER_ARMOR:
      item = LEATHER_ARMOR;
      break;

    case ID_PLATE_ARMOR:
      item = PLATE_ARMOR;
      break;

    case ID_BLUE_TUNIC:
      item = BLUE_TUNIC;
      break;

    case ID_HP_POTION:
      item = HP_POTION;
      break;

    case ID_MANA_POTION:
      item = MANA_POTION;
      break;

    case ID_SWORD:
      item = SWORD;
      break;

    case ID_AXE:
      item = AXE;
      break;

    case ID_HAMMER:
      item = HAMMER;
      break;

    case ID_SIMPLE_BOW:
      item = SIMPLE_BOW;
      break;

    case ID_COMPOUND_BOW:
      item = COMPUND_BOW;
      break;

    case ID_ASH_STICK:
      item = ASH_STICK;
      break;

    case ID_KNOTTY_STAFF:
      item = GNARLED_STAFF;
      break;

    case ID_CRIMPED_STAFF:
      item = CRIMP_STAFF;
      break;

    case ID_ELVEN_ELUDE:
      item = ELVEN_FLUTE;
      break;
  }
  return item;
}
