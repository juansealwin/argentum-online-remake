#include "map.h"

Map::Map(int id_player, int id_background_path, SDL_Renderer* ren,
         int scr_width, int scr_height)
    : id_hero(id_player),
      renderer(ren),
      screen_width(scr_width),
      screen_height(scr_height) {
  background_texture.loadTexture(ID_MAP_GRASS, renderer);
  map_piece = {0, 0, screen_width, screen_height};
  viewport = {0, 0, screen_width, screen_height};
}

Map::~Map() {
  cleanCharactersVector();
  renderer = nullptr;
}

void Map::updateCharacter(int id, int new_x, int new_y) {
  characters[id].updatePosition(new_x, new_y);
  if (id == id_hero) updateMap(new_x, new_y);
}

void Map::updateMap(int new_x, int new_y) {
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
  renderCharacters();
}

void Map::changeMap(int id_new_map) {
  cleanCharactersVector();
  background_texture.loadTexture(id_new_map, renderer);
}

void Map::loadCharacter(SDL_Renderer* ren, character_t char_type, int id, int x,
                        int y) {
  if (char_type == HUMAN)
    characters[id] = Human(ren, id, x, y);
  else if (char_type == ELF)
    characters[id] = Elf(ren, id, x, y);
  else if (char_type == GNOME)
    characters[id] = Gnome(ren, id, x, y);
  else if (char_type == DWARF)
    characters[id] = Dwarf(ren, id, x, y);
  else if (char_type == SPIDER)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == GOBLIN)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == SKELETON)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == ZOMBIE)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == MERCHANT)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == BANKER)
    characters[id] = Npc(ren, char_type, x, y);
  else if (char_type == PRIEST)
    characters[id] = Npc(ren, char_type, x, y);
}

void Map::renderCharacters() {
  std::map<int, Character>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    // El personaje DEBE estar dentro del viewport
    if ((map_piece.x <= it->second.getX()) &&
        (it->second.getX() <= map_piece.x + screen_width))
      if ((map_piece.y <= it->second.getY()) &&
          (it->second.getY() <= map_piece.y + screen_height)) {
        it->second.render(map_piece.x, map_piece.y);
      }
  }
}

void Map::cleanCharactersVector() {
  /*std::vector<Character*>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    delete *it;
    it = characters.erase(it);
  }*/
}