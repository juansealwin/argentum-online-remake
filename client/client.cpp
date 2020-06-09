#include "client.h"


Client::Client(const char *host, const char *port) {
    //this->socket.connect(host, port);
}

const bool Client::valid_request(std::string &request) {
    return true;
}

void Client::play() {
    SdlWindow ventana(800,600);
    ventana.fill();
    Texture image_lobby;
    image_lobby.loadTexture(PATH_IMG_LOBBY, ventana.getRenderer());
    image_lobby.render(ventana.getRenderer());
    ventana.render();
    SDL_Delay(3000);
    ventana.~SdlWindow();
}

void Client::send_request(const unsigned char* request, std::size_t size) {
    ClientProtocol::send_request(socket, request, size);
}

std::vector<unsigned char> Client::get_response() {
    return ClientProtocol::receive_request_response(socket);
}

