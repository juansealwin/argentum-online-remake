#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>

#include "argentum_game.h"
#include "common_socket.h"
#include "server_protocol.h"
#include "thread.h"

class ClientHandler : public Thread {
 public:
  // Instancia un nuevo manejador de clientes para que juege
  // a el juego ArgentumGame recibido por parametro (Es la sala)
  ClientHandler(Socket socket, ArgentumGame *game);
  ~ClientHandler() override;
  /*
  Corre hasta que termine el juego, el juego terminara cuando:
  - El cliente adivina el numero
  - El cliente avise que se rinda
  - El cliente termina su decimo intento sin adivinar el numero.
  */
  void run() override;
  // Devuelve True mientras el juego siga en curso
  bool is_alive();

 private:
  ArgentumGame *game;
  Socket peer_socket;

  bool alive = true;
  /* Recibe un nuevo comando del cliente
   (AYUDA, RENDIRSE, o un numero de 3 cifras)*/
  unsigned char receive_request();
  /*Envia una respuesta al comando recibido, segun como afecte el comando
  al juego*/
  void send_response(const unsigned char *response, const uint16_t *size);
};

#endif  // CLIENTHANDLER_H
