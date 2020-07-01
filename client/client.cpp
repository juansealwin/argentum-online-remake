#include "client.h"

#include <iostream>

#include "login_command_dto.h"

Client::Client(const char* host, const char* port) : player_id(15) {
  Socket socket;
  socket.connect(host, port);
  this->socket = std::move(socket);
  is_running = true;
}

Client::~Client() {}

void Client::play() {
  CommandsBlockingQueue commands_to_send;
  ProtectedMap protected_map(player_id, 800, 600);
  EventsQueue event_queue;
  // TODO: tambien hay que mandar el usuario
  LoginCommandDTO* login_command = new LoginCommandDTO(0);
  commands_to_send.push(login_command);

  // TODO: el server me devuelve el player_id
  CommandsSender sender(commands_to_send, socket);

  GameUpdater updater(protected_map, socket, is_running);
  GameRenderer renderer(800, 600, protected_map, event_queue);
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
  updater.join();
  sender.join();
}
