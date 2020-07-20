#include "client.h"

template <typename T>
T extract(const std::vector<unsigned char>& v, int pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  return value;
}

Client::Client(const char* host, const char* port, WindowGame& new_window)
    : window_game(new_window) {
  Socket socket;
  if (socket.connect(host, port) == EXIT_SUCCESS) {
    this->socket = std::move(socket);
    is_running = true;
  } else {
    throw ConnectionException("%s", MSG_ERROR_CONNECTING_SERVER);
  }
}

Client::~Client() {}

void Client::do_handshake(std::string user_name, std::string race_selected,
                          std::string class_selected) {
  // Mandamos la información del usuario y preferencias
  LoginCommandDTO* login_command =
      new LoginCommandDTO(0, user_name, race_selected, class_selected);

  Protocol::send_command(socket, login_command);
  delete login_command;
  std::cout<<"SOY "<<race_selected<<" Y "<<class_selected<<std::endl;
  // Recibimos el id y el mapa inicial
  std::vector<unsigned char> starting_info;
  Protocol::receive_notification(socket, starting_info);
  player_id = ntohs(extract<uint16_t>(starting_info, 1));
  initial_map = ntohs(extract<uint16_t>(starting_info, 3));
}

void Client::play() {
  ProtectedMap protected_map(player_id, window_game.get_screen_width(),
                             window_game.get_screen_height(), initial_map);
  EventsQueue event_queue;
  CommandsBlockingQueue commands_to_send;

  CommandsSender sender(commands_to_send, socket);
  GameUpdater updater(player_id, protected_map, socket, is_running);
  GameRenderer renderer(
      window_game.get_renderer(), window_game.get_screen_width(),
      window_game.get_screen_height(), protected_map, event_queue);
  EventHandler event_handler(commands_to_send, event_queue, is_running);
  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al
  // server

  sender.start();
  updater.start();
  renderer.start();
  event_handler.get_events();

  while (is_running) {
  }
  // Una vez que se cierra el juego se hace join de los subprocesos
  renderer.join();
  sender.join();
  updater.join();
}
