#include "client.h"

Client::Client(const char *host, const char *port) {
    // this->socket.connect(host, port);
}

const bool Client::valid_request(std::string &request) { return true; }

void Client::play() {
    GameWindow game_window(800, 600);
    Human humano;
    SDL_Rect mov;
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
                        mov = humano.moveUp();
                        break;

                        /*case SDLK_DOWN:

                        break;

                        case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[
                        KEY_PRESS_SURFACE_LEFT ]; break;

                        case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[
                        KEY_PRESS_SURFACE_RIGHT ]; break;*/

                    default:

                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(game_window.getRenderer(), 0xFF, 0xFF, 0xFF,
                               0xFF);
        SDL_RenderClear(game_window.getRenderer());

        // renderizar moveup
        game_window.getTexture()->render(game_window.getRenderer(), &mov, 0,0);
        // Update screen
        SDL_RenderPresent(game_window.getRenderer());
    }
}

void Client::send_request(const unsigned char *request, std::size_t size) {
    ClientProtocol::send_request(socket, request, size);
}

std::vector<unsigned char> Client::get_response() {
    return ClientProtocol::receive_request_response(socket);
}
