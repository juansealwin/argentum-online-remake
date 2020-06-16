#include "background_map.h"

BackgroundMap::BackgroundMap(int id_background_path, SDL_Renderer* ren,
                             int scr_width, int scr_height)
    : renderer(ren), screen_width(scr_width), screen_height(scr_height) {
  background_texture.loadTexture(ID_MAP_GRASS, renderer);
  map_piece = {0, 0, screen_width, screen_height};
  viewport = {0, 0, screen_width, screen_height};
}

BackgroundMap::~BackgroundMap() { renderer = nullptr; }

void BackgroundMap::update(int new_x, int new_y) {
  map_piece.x += new_x;
  map_piece.y += new_y;
  if (map_piece.x > MAP_SIZE - screen_width) {
    viewport.w = screen_width - (map_piece.x - (MAP_SIZE - screen_width));
    map_piece.w = screen_width - (map_piece.x - (MAP_SIZE - screen_width));
  } else {
    viewport.w = screen_width;
    map_piece.w = screen_width;
  }
  if (map_piece.y > MAP_SIZE - screen_height) {
    viewport.h = screen_height - (map_piece.y - (MAP_SIZE - screen_height));
    map_piece.h = screen_height - (map_piece.y - (MAP_SIZE - screen_height));
  } else {
    viewport.h = screen_height;
    map_piece.h = screen_height;
  }
  if (map_piece.x < 0) {
    viewport.x = -map_piece.x;
    map_piece.w = screen_width - map_piece.x;
  } else {
    viewport.x = 0;
    map_piece.w = screen_width;
  }
  if (map_piece.y < 0) {
    viewport.y = -map_piece.y;
    map_piece.h = screen_height - map_piece.y;
  } else {
    viewport.y = 0;
    map_piece.h = screen_height;
  }
}

void BackgroundMap::render() {
  // SDL_RenderCopy()
  background_texture.render(renderer, &map_piece, &viewport);
}

void BackgroundMap::changeMap(int id_new_map) {
  background_texture.loadTexture(id_new_map, renderer);
}