#ifndef PROTECTED_MAP_H
#define PROTECTED_MAP_H

#include <condition_variable>
#include <mutex>

#include "entity_status.h"
#include "game.h"
#include "types.h"
#include "ui_status.h"

// Por defecto cuando se agrega un personaje no esta afectado por un hechizo
typedef struct {
  id_texture_t type_spell = ID_NULL;
  int lifetime = 0;
} spellbound_t;

class ProtectedMap {
 private:
  std::unique_ptr<Game> read_map;
  std::unique_ptr<Game> write_map;
  std::map<int, EntityStatus> current_status;
  std::map<int, spellbound_t> characters_afected;
  UIStatus current_ui_status;
  std::vector<sound_t> incoming_sounds;
  std::mutex block_maps;
  std::condition_variable cv;

 public:
  ProtectedMap(int, int, int, int);
  ~ProtectedMap();
  void map_reader(Game&, UIStatus&, std::vector<sound_t>&);
  void copy_buffer(UIStatus&);
  void map_writer(std::map<int, EntityStatus>&, map_t&);
};

#endif