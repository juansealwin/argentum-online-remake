#include "game.h"

Game::Game(int id_player, id_texture_t id_background, int scr_width,
           int scr_height)
    : id_hero(id_player),
      type_map(id_background),
      screen_width(scr_width),
      screen_height(scr_height) {
  map_piece = {0, 0, screen_width, screen_height};
  viewport = {0, 0, screen_width, screen_height};
}

Game::Game(const Game& other_game) {
  id_hero = other_game.id_hero;
  screen_width = other_game.screen_width;
  screen_height = other_game.screen_height;
  type_map = other_game.type_map;
  map_piece = other_game.map_piece;
  viewport = other_game.viewport;
  // hay que verificar esto
  characters = other_game.characters;
}

Game& Game::operator=(const Game& other_game) {
  id_hero = other_game.id_hero;
  screen_width = other_game.screen_width;
  screen_height = other_game.screen_height;
  type_map = other_game.type_map;
  map_piece = other_game.map_piece;
  viewport = other_game.viewport;
  // hay que verificar esto
  characters = other_game.characters;
}

Game::~Game() {
  characters.clear();
}

void Game::update_character(int id, int new_x, int new_y) {
  characters[id].update_position(new_x, new_y);
  if (id == id_hero) update_map(new_x, new_y);
}

void Game::update_map(int new_x, int new_y) {
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

void Game::render(SDL_Renderer* renderer) {
  texture_manager->get_texture(type_map).render(renderer, &map_piece,
                                                &viewport);
  render_characters(renderer);
}

// Por ahora no la usariamos
/*
void Map::change_map(int id_new_map) {
  clean_characters_vector();
  background_texture.load_texture(paths->get_path_texture(id_new_map),
                                  renderer);
}
*/

void Game::load_character(character_t char_type, int id, int x, int y) {
  if (char_type == HUMAN || char_type == ELF || char_type == GNOME ||
      char_type == DWARF)
    characters[id] = PlayableCharacter(char_type, x, y);
  else
    characters[id] = Npc(char_type, x, y);
}

void Game::render_characters(SDL_Renderer* renderer) {
  std::map<int, Character>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    // El personaje DEBE estar dentro del viewport
    if ((map_piece.x <= it->second.get_x()) &&
        (it->second.get_x() <= map_piece.x + screen_width))
      if ((map_piece.y <= it->second.get_y()) &&
          (it->second.get_y() <= map_piece.y + screen_height)) {
        it->second.render(renderer, map_piece.x, map_piece.y);
      }
  }
}

void Game::clean_character(int i) { characters.erase(i); }