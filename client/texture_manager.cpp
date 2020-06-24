#include "texture_manager.h"

TextureManager* TextureManager::instance_texture_manager = nullptr;

TextureManager* TextureManager::get_instance() {
  if (instance_texture_manager == NULL) {
    instance_texture_manager = new TextureManager();
  }
  return (instance_texture_manager);
}

TextureManager::TextureManager() {
  /* PLAYABLE CHARACTER TEXTURES */
  map[ID_HUMAN] = Texture("humano.png", renderer);
  map[ID_HUMAN_HEAD] = Texture("cabeza_humano.png", renderer);
  map[ID_ELF] = Texture("elfo.png", renderer);
  map[ID_ELF_HEAD] = Texture("cabeza_elfo.png", renderer);
  map[ID_GNOME] = Texture("gnomo.png", renderer);
  map[ID_GNOME_HEAD] = Texture("cabeza_gnomo.png", renderer);
  map[ID_DWARF] = Texture("enano.png", renderer);
  map[ID_DWARF_HEAD] = Texture("cabeza_enano.png", renderer);
  /*

  /* NPC TEXTURES */
  map[ID_SPIDER] = Texture("araña.png", renderer);
  map[ID_SKELETON] = Texture("esqueleto.png", renderer);
  map[ID_GOBLIN] = Texture("goblin.png", renderer);
  map[ID_ZOMBIE] = Texture("zombie.png", renderer);
  map[ID_PRIEST] = Texture("sacerdote.png", renderer);
  map[ID_MERCHANT] = Texture("comerciante.png", renderer);
  map[ID_BANKER] = Texture("banquero.png", renderer);

  /* MAP TEXTURES */
  map[ID_MAP_GRASS] = Texture("mapa_hierba.png", renderer);
}

TextureManager::~TextureManager() {}

Texture& TextureManager::get_texture(id_texture_t id) {
  return map[id];
}