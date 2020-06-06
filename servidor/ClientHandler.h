#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "../red/Socket.h"
#include "../utils/Thread.h"
#include <string>
#include "../protocol/ServerProtocol.h"

class ClientHandler : public Thread {
public:
    //Instancia un nuevo manejador de clientes para que juege 
    //a un juego de GuessNumberGame utilizando el numero 'number'
    ClientHandler
        (Socket socket);
    ~ClientHandler() override;
    /*
    Corre hasta que termine el juego, el juego terminara cuando:
    - El cliente adivina el numero
    - El cliente avise que se rinda
    - El cliente termina su decimo intento sin adivinar el numero.
    */
    void run() override;
    // Devuelve True mientras el juego siga en curso
    const bool is_alive();

private:
    Socket peer_socket;

    bool alive = true;
    /* Recibe un nuevo comando del cliente
     (AYUDA, RENDIRSE, o un numero de 3 cifras)*/
    unsigned char receive_request();
    /*Envia una respuesta al comando recibido, segun como afecte el comando
    al juego*/
    void send_response(const unsigned char* response, const uint16_t *size);
};


#endif //CLIENTHANDLER_H
