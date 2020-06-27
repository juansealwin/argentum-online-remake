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

  /* HELMETS AND HATS TEXTURES*/
  map[ID_MAGIC_HAT] = Texture("araña.png", renderer);
  map[ID_MAGIC_HAT_EQUIPPED] = Texture("esqueleto.png", renderer);
  map[ID_HOOD] = Texture("goblin.png", renderer);
  map[ID_HOOD_EQUIPPED] = Texture("zombie.png", renderer);
  map[ID_IRON_HELMET] = Texture("sacerdote.png", renderer);
  map[ID_IRON_HELMET_EQUIPPED] = Texture("comerciante.png", renderer);

  /* ARMOR TEXTURES */
  map[ID_LEATHER_ARMOR] = Texture("armadura_cuero.png", renderer);
  map[ID_LEATHER_ARMOR_EQUIPPED] = Texture("armadura_cuero_equipada.png", renderer);
  map[ID_LEATHER_ARMOR_XS_EQUIPPED] = Texture("armadura_cuero_xs_equipada.png", renderer);
  map[ID_PLATE_ARMOR] = Texture("armadura_placas.png", renderer);
  map[ID_PLATE_ARMOR_EQUIPPED] = Texture("armadura_placas_equipada.png", renderer);
  map[ID_PLATE_ARMOR_XS_EQUIPPED] = Texture("armadura_placas_xs_equipada.png", renderer);
  map[ID_BLUE_TUNIC] = Texture("tunica_azul.png", renderer);
  map[ID_BLUE_TUNIC_EQUIPPED] = Texture("tunica_azul_equipada.png", renderer);

  /* WEAPON TEXTURES */
  map[ID_COMPOUND_BOW] = Texture("arco_compuesto.png", renderer);
  map[ID_COMPOUND_BOW_EQUIPPED] =
      Texture("arco_compuesto_equipado.png", renderer);
  map[ID_SIMPLE_BOW] = Texture("arco_simple.png", renderer);
  map[ID_SIMPLE_BOW_EQUIPPED] = Texture("arco_simple_equipado.png", renderer);
  map[ID_SWORD] = Texture("espada.png", renderer);
  map[ID_SWORD_EQUIPPED] = Texture("espada_equipada.png", renderer);
  map[ID_AXE] = Texture("hacha.png", renderer);
  map[ID_AXE_EQUIPPED] = Texture("hacha_equipada.png", renderer);
  map[ID_HAMMER] = Texture("martillo.png", renderer);
  map[ID_HAMMER_EQUIPPED] = Texture("martillo_equipado.png", renderer);
  map[ID_KNOTTY_STAFF] = Texture("baculo_nudoso.png", renderer);
  map[ID_KNOTTY_STAFF_EQUIPPED] =
      Texture("baculo_nudoso_equipado.png", renderer);
  map[ID_ASH_STICK] = Texture("vara_fresno.png", renderer);
  map[ID_ASH_STICK_EQUIPPED] = Texture("vara_fresno_equipada.png", renderer);
  map[ID_CRIMPED_STAFF] = Texture("baculo_engarsado.png", renderer);
  map[ID_CRIMPED_STAFF_EQUIPPED] =
      Texture("baculo_engarsado_equipado.png", renderer);

  /* SHIELD TEXTURES */
  map[ID_IRON_SHIELD] = Texture("escudo_hierro.png", renderer);
  map[ID_IRON_SHIELD_EQUIPPED] =
      Texture("escudo_hierro_equipado.png", renderer);
  map[ID_TURTLE_SHIELD] = Texture("escudo_tortuga.png", renderer);
  map[ID_TURTLE_SHIELD_EQUIPPED] = Texture("escudo_tortuga_equipado.png", renderer);
}

TextureManager::~TextureManager() {}

Texture& TextureManager::get_texture(id_texture_t id) { return map[id]; }