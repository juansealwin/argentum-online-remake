#include <iostream>
#include "ClientListener.h"
#include "ClientHandler.h"
#include "../protocol/ServerProtocol.h"
ClientListener::ClientListener(const char *port) {
    Socket server_socket;
    server_socket.bind_and_listen(port);
    this->server_socket = std::move(server_socket);
    for (int i = 0; i < 10; i++) {
        games.emplace_back(new ArgentumGame(i));
    }
}

ClientListener::~ClientListener() {
    join();
}

void ClientListener::stop_listening() {
    for (ClientHandler *c : clients) {
        delete c;
    }
    for (ArgentumGame *g : games) {
        delete g;
    }
    server_socket.close();
}
void ClientListener::run() {
    while (true) {
        Socket clientSkt;
        try {
            clientSkt = this->server_socket.accept();
        }
        catch (std::invalid_argument) {
            break;
        }
        unsigned int room_number = ServerProtocol::receive_room_no(clientSkt);
        ClientHandler *client = new ClientHandler
                                    (std::move(clientSkt), games[room_number]);
        clients.push_back(client);
        client->start();
        garbage_collector();
    }
}

void ClientListener::garbage_collector() {
    std::list<ClientHandler *>::iterator it = clients.begin();
    while (it != clients.end()) {
        if (!(*it)->is_alive()) {
            delete *it;
            it = clients.erase(it);
        } else {
            it++;
        }
    }
}
