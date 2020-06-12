#include "client.h"

Client::Client(const char *host, const char *port) {
    // this->socket.connect(host, port);
}

const bool Client::valid_request(std::string &request) { return true; }

void Client::play() {
    GameWindow game_window(800, 600);
    Elf elfo;
    SDL_Rect cuerpo = {0, 0, 25, 45};
    SDL_Rect cabeza = {0, 0, 17, 16};
    // Main loop flag
    bool quit = false;
    // Event handler
    SDL_Event e;
    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // User presses a key
            else if (e.type == SDL_KEYDOWN) {
                // Select surfaces based on key press
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        cuerpo = elfo.move(MOVE_UP);
                        cabeza = elfo.getFaceProfile(MOVE_UP);
                        break;

                    case SDLK_DOWN:
                        cuerpo = elfo.move(MOVE_DOWN);
                        cabeza = elfo.getFaceProfile(MOVE_DOWN);
                        break;

                    case SDLK_LEFT:
                        cuerpo = elfo.move(MOVE_LEFT);
                        cabeza = elfo.getFaceProfile(MOVE_LEFT);
                        break;

                    case SDLK_RIGHT:
                        cuerpo = elfo.move(MOVE_RIGHT);
                        cabeza = elfo.getFaceProfile(MOVE_RIGHT);
                        break;

                    default:

                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(game_window.getRenderer(), 0, 0, 0, 0xFF);
        SDL_RenderClear(game_window.getRenderer());
        // renderizar moveup
        // humano_textura.render(game_window.getRenderer(), &mov, 400, 300);
        game_window.getTexture(0)->render(game_window.getRenderer(), &cuerpo,
                                          400 - (ELF_WIDTH/2), 300 - (ELF_HEIGHT/2));
        game_window.getTexture(1)->render(game_window.getRenderer(), &cabeza,
                                          400-(ELF_HEAD_WIDTH/2), 300 -(ELF_HEIGHT/2) - (ELF_HEAD_HEIGHT/2));

        // Update screen
        SDL_RenderPresent(game_window.getRenderer());
        // SDL_Delay(3000);
    }
}

void Client::send_request(const unsigned char *request, std::size_t size) {
    ClientProtocol::send_request(socket, request, size);
}

std::vector<unsigned char> Client::get_response() {
    return ClientProtocol::receive_request_response(socket);
}
