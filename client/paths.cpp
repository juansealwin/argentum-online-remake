#include "paths.h"

Paths::Paths() {
  /* CHARACTER PATHS */
  map_paths[ID_HUMAN] = "humano.png";
  map_paths[ID_HUMAN_HEAD] = "cabeza_humano.png";
  map_paths[ID_ELF] = "elfo.png";
  map_paths[ID_ELF_HEAD] = "cabeza_elfo.png";
  map_paths[ID_GNOME] = "gnomo.png";
  map_paths[ID_GNOME_HEAD] = "cabeza_gnomo.png";
  map_paths[ID_DWARF] = "enano.png";
  map_paths[ID_DWARF_HEAD] = "cabeza_enano.png";

  /* MAP PATHS */
  map_paths[ID_MAP_GRASS] = "mapa_hierba.png";
}

Paths::~Paths() {}

const char* Paths::getPathTexture(int id) {
  return map_paths[id].c_str();
}