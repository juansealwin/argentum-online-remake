#include "background_map.h"

BackgroundMap::BackgroundMap(std::string background_path, SDL_Renderer* ren)
    : renderer(ren) {
  background_texture.loadTexture(background_path, renderer);
  map_piece = {0, 0, 800, 600};
}

BackgroundMap::~BackgroundMap() {
  renderer = nullptr;
  background_texture.free();
}

void BackgroundMap::update(int new_x, int new_y) {
  map_piece.x += new_x;
  map_piece.y += new_y;
}

void BackgroundMap::render() {
  background_texture.render(renderer, &map_piece, 0, 0);
}

void BackgroundMap::changeMap(std::string new_map) {
  background_texture.loadTexture(new_map, renderer);
}