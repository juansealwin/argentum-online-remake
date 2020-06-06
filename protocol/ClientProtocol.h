#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include "../red/Socket.h"
#include <vector>
namespace ClientProtocol {
	//Envia el mensaje a traves del socket al servidor con el cual
	//el cliente se esta comunicando
    void send_request
    (const Socket& skt, const unsigned char *message, const std::size_t size);
    //recibe y devuelve la respuesta del servidor
    std::vector<unsigned char> receive_request_response(const Socket& skt);
}

#endif //CLIENT_PROTOCOL_H
