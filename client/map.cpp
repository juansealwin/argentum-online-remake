#include "map.h"

Map::Map(int id_player, int id_background_path, SDL_Renderer* ren,
         int scr_width, int scr_height)
    : id_hero(id_player),
      renderer(ren),
      screen_width(scr_width),
      screen_height(scr_height) {
  background_texture.load_texture(paths->get_path_texture(ID_MAP_GRASS),
                                  renderer);
  map_piece = {0, 0, screen_width, screen_height};
  viewport = {0, 0, screen_width, screen_height};
}

Map::~Map() {
  clean_characters_vector();
  renderer = nullptr;
}

void Map::update_character(int id, int new_x, int new_y) {
  characters[id].update_position(new_x, new_y);
  if (id == id_hero) update_map(new_x, new_y);
}

void Map::update_map(int new_x, int new_y) {
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

void Map::render() {
  background_texture.render(renderer, &map_piece, &viewport);
  render_characters();
}
// Por ahora no la usariamos
/*
void Map::change_map(int id_new_map) {
  clean_characters_vector();
  background_texture.load_texture(paths->get_path_texture(id_new_map),
                                  renderer);
}
*/

void Map::load_character(SDL_Renderer* ren, character_t char_type, int id,
                         int x, int y) {
  if (char_type == HUMAN || char_type == ELF || char_type == GNOME ||
      char_type == DWARF)
    characters[id] = PlayableCharacter(ren, char_type, x, y);
  else
    characters[id] = Npc(ren, char_type, x, y);
}

void Map::render_characters() {
  std::map<int, Character>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    // El personaje DEBE estar dentro del viewport
    if ((map_piece.x <= it->second.get_x()) &&
        (it->second.get_x() <= map_piece.x + screen_width))
      if ((map_piece.y <= it->second.get_y()) &&
          (it->second.get_y() <= map_piece.y + screen_height)) {
        it->second.render(map_piece.x, map_piece.y);
      }
  }
}

void Map::clean_characters_vector() {
  /*std::vector<Character*>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    delete *it;
    it = characters.erase(it);
  }*/
}