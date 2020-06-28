#include "texture_manager.h"

TextureManager& TextureManager::get_instance() {
  static TextureManager instance_texture_manager;
  return instance_texture_manager;
}

TextureManager::TextureManager() {
  std::map<id_texture_t, Texture*>::iterator it;
  for (it = map.begin() ; it != map.end(); it++) {
    it->second->~Texture();
    delete it->second;
  }
}

void TextureManager::load_textures(SDL_Renderer* renderer) {
  /* PLAYABLE CHARACTER TEXTURES */
  map[ID_HUMAN] = new Texture("humano.png", renderer);
  map[ID_HUMAN_HEAD] = new Texture("cabeza_humano.png", renderer);
  map[ID_ELF] = new Texture("elfo.png", renderer);
  map[ID_ELF_HEAD] = new Texture("cabeza_elfo.png", renderer);
  map[ID_GNOME] = new Texture("gnomo.png", renderer);
  map[ID_GNOME_HEAD] = new Texture("cabeza_gnomo.png", renderer);
  map[ID_DWARF] = new Texture("enano.png", renderer);
  map[ID_DWARF_HEAD] = new Texture("cabeza_enano.png", renderer);

  /* NPC TEXTURES */
  map[ID_SPIDER] = new Texture("araña.png", renderer);
  map[ID_SKELETON] = new Texture("esqueleto.png", renderer);
  map[ID_GOBLIN] = new Texture("goblin.png", renderer);
  map[ID_ZOMBIE] = new Texture("zombie.png", renderer);
  map[ID_PRIEST] = new Texture("sacerdote.png", renderer);
  map[ID_MERCHANT] = new Texture("comerciante.png", renderer);
  map[ID_BANKER] = new Texture("banquero.png", renderer);

  /* MAP TEXTURES */
  map[ID_MAP_GRASS] = new Texture("mapa_hierba.png", renderer);

  /* HELMETS AND HATS TEXTURES*/
  map[ID_MAGIC_HAT] = new Texture("araña.png", renderer);
  map[ID_MAGIC_HAT_EQUIPPED] = new Texture("esqueleto.png", renderer);
  map[ID_HOOD] = new Texture("goblin.png", renderer);
  map[ID_HOOD_EQUIPPED] = new Texture("zombie.png", renderer);
  map[ID_IRON_HELMET] = new Texture("sacerdote.png", renderer);
  map[ID_IRON_HELMET_EQUIPPED] = new Texture("comerciante.png", renderer);

  /* ARMOR TEXTURES */
  map[ID_LEATHER_ARMOR] = new Texture("armadura_cuero.png", renderer);
  map[ID_LEATHER_ARMOR_EQUIPPED] =
      new Texture("armadura_cuero_equipada.png", renderer);
  map[ID_LEATHER_ARMOR_XS_EQUIPPED] =
      new Texture("armadura_cuero_xs_equipada.png", renderer);
  map[ID_PLATE_ARMOR] = new Texture("armadura_placas.png", renderer);
  map[ID_PLATE_ARMOR_EQUIPPED] =
      new Texture("armadura_placas_equipada.png", renderer);
  map[ID_PLATE_ARMOR_XS_EQUIPPED] =
      new Texture("armadura_placas_xs_equipada.png", renderer);
  map[ID_BLUE_TUNIC] = new Texture("tunica_azul.png", renderer);
  map[ID_BLUE_TUNIC_EQUIPPED] =
      new Texture("tunica_azul_equipada.png", renderer);

  /* WEAPON TEXTURES */
  map[ID_COMPOUND_BOW] = new Texture("arco_compuesto.png", renderer);
  map[ID_COMPOUND_BOW_EQUIPPED] =
      new Texture("arco_compuesto_equipado.png", renderer);
  map[ID_SIMPLE_BOW] = new Texture("arco_simple.png", renderer);
  map[ID_SIMPLE_BOW_EQUIPPED] =
      new Texture("arco_simple_equipado.png", renderer);
  map[ID_SWORD] = new Texture("espada.png", renderer);
  map[ID_SWORD_EQUIPPED] = new Texture("espada_equipada.png", renderer);
  map[ID_AXE] = new Texture("hacha.png", renderer);
  map[ID_AXE_EQUIPPED] = new Texture("hacha_equipada.png", renderer);
  map[ID_HAMMER] = new Texture("martillo.png", renderer);
  map[ID_HAMMER_EQUIPPED] = new Texture("martillo_equipado.png", renderer);
  map[ID_KNOTTY_STAFF] = new Texture("baston_nudoso.png", renderer);
  map[ID_KNOTTY_STAFF_EQUIPPED] =
      new Texture("baston_nudoso_equipado.png", renderer);
  map[ID_ASH_STICK] = new Texture("vara_fresno.png", renderer);
  map[ID_ASH_STICK_EQUIPPED] =
      new Texture("vara_fresno_equipada.png", renderer);
  map[ID_CRIMPED_STAFF] = new Texture("baculo_engarzado.png", renderer);
  map[ID_CRIMPED_STAFF_EQUIPPED] =
      new Texture("baculo_engarzado_equipado.png", renderer);

  /* SHIELD TEXTURES */
  map[ID_IRON_SHIELD] = new Texture("escudo_hierro.png", renderer);
  map[ID_IRON_SHIELD_EQUIPPED] =
      new Texture("escudo_hierro_equipado.png", renderer);
  map[ID_TURTLE_SHIELD] = new Texture("escudo_tortuga.png", renderer);
  map[ID_TURTLE_SHIELD_EQUIPPED] =
      new Texture("escudo_tortuga_equipado.png", renderer);
}

TextureManager::~TextureManager() {}

Texture& TextureManager::get_texture(id_texture_t id) { return *map[id]; }