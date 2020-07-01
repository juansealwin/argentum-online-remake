#include "client.h"

template <typename T>
T extract(const std::vector<unsigned char>& v, int pos) {
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  return value;
}

Client::Client(const char* host, const char* port) {
  Socket socket;
  socket.connect(host, port);
  this->socket = std::move(socket);
  is_running = true;
}

Client::~Client() {}

void Client::play() {
  CommandsBlockingQueue commands_to_send;
  // TODO: tambien hay que mandar el usuario
  LoginCommandDTO* login_command = new LoginCommandDTO(0);
  commands_to_send.push(login_command);

  CommandsSender sender(commands_to_send, socket);
  sender.start();

  // TODO: Server envia nombre de mapa ademas del id del jugador

  // Esto probablmente quede mejor moverlo
  std::vector<unsigned char> starting_info;
  Protocol::receive_notification(socket, starting_info);
  player_id = ntohs(extract<uint16_t>(starting_info, 1));
  ProtectedMap protected_map(player_id, 800, 600);
  EventsQueue event_queue;

  GameUpdater updater(protected_map, socket, is_running);
  GameRenderer renderer(800, 600, protected_map, event_queue);
  EventHandler event_handler(commands_to_send, event_queue, is_running);
  // Lanzo los hilos para renderizar, actualizar el modelo, enviar datos al
  // server
  
  updater.start();
  renderer.start();
  event_handler.get_events();

  while (is_running) {
  }

  // Una vez que se cierra el juego se hace join de los subprocesos
  renderer.join();
  updater.join();
  sender.join();
}
