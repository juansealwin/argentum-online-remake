#include "lobby.h"

Lobby::Lobby(SDL_Renderer* ren) : renderer(ren) {
  log_in = Texture("log_in.png", renderer);
  character_selection = Texture("log_in.png", renderer);
}

Lobby::~Lobby() {}

void start_lobby() {

 

}