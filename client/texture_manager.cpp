#include "texture_manager.h"

TextureManager& TextureManager::get_instance() {
  static TextureManager instance_texture_manager;
  return instance_texture_manager;
}

TextureManager::TextureManager() {
  std::map<id_texture_t, Texture*>::iterator it;
  for (it = map.begin(); it != map.end(); it++) {
    it->second->~Texture();
    delete it->second;
  }
}

void TextureManager::load_textures(SDL_Renderer* renderer) {
  /* UI */
  map[ID_UI] = new Texture("ui.png", renderer);
  map[ID_SELECTOR] = new Texture("selector_item.png", renderer);
  map[ID_ITEM_EQUIPPED] = new Texture("opcion_equipado.png", renderer);

  /* PLAYABLE CHARACTER TEXTURES */
  map[ID_MEDITATION] = new Texture("meditar.png", renderer);
  map[ID_CORPSE] = new Texture("muerto_cuerpo.png", renderer);
  map[ID_CORPSE_HEAD] = new Texture("muerto_cabeza.png", renderer);
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
  map[ID_MAP_GRASS_BACKGROUND] = new Texture("mapa_hierba_fondo.png", renderer);
  map[ID_MAP_GRASS_OBJECTS] = new Texture("mapa_hierba_objetos.png", renderer);
  map[ID_MAP_DESERT_BACKGROUND] =
      new Texture("mapa_desierto_fondo.png", renderer);
  map[ID_MAP_DESERT_OBJECTS] =
      new Texture("mapa_desierto_objetos.png", renderer);
  map[ID_MAP_ARGAL_BACKGROUND] = new Texture("mapa_argal_fondo.png", renderer);
  map[ID_MAP_ARGAL_OBJECTS] = new Texture("mapa_argal_objetos.png", renderer);

  /* HELMETS AND HATS TEXTURES*/
  map[ID_MAGIC_HAT] = new Texture("sombrero_magico.png", renderer);
  map[ID_MAGIC_HAT_EQUIPPED] =
      new Texture("sombrero_magico_equipado.png", renderer);
  map[ID_HOOD] = new Texture("capucha.png", renderer);
  map[ID_HOOD_EQUIPPED] = new Texture("capucha_equipada.png", renderer);
  map[ID_IRON_HELMET] = new Texture("casco_hierro.png", renderer);
  map[ID_IRON_HELMET_EQUIPPED] =
      new Texture("casco_hierro_equipado.png", renderer);

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
  map[ID_BLUE_TUNIC_XS_EQUIPPED] =
      new Texture("tunica_azul_xs_equipada.png", renderer);

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
  map[ID_DEADLY_STAFF] = new Texture("baculo_mortal.png", renderer);
  map[ID_DEADLY_STAFF_EQUIPPED] =
      new Texture("baculo_mortal_equipado.png", renderer);
  map[ID_ELVEN_ELUDE] = new Texture("laud_elfico.png", renderer);
  map[ID_ELVEN_ELUDE_EQUIPPED] =
      new Texture("laud_elfico_equipado.png", renderer);

  /* SHIELD TEXTURES */
  map[ID_IRON_SHIELD] = new Texture("escudo_hierro.png", renderer);
  map[ID_IRON_SHIELD_EQUIPPED] =
      new Texture("escudo_hierro_equipado.png", renderer);
  map[ID_TURTLE_SHIELD] = new Texture("escudo_tortuga.png", renderer);
  map[ID_TURTLE_SHIELD_EQUIPPED] =
      new Texture("escudo_tortuga_equipado.png", renderer);

  /* OTHER ITEMS */
  map[ID_GOLD] = new Texture("oro.png", renderer);
  map[ID_HP_POTION] = new Texture("pocion_vida.png", renderer);
  map[ID_MANA_POTION] = new Texture("pocion_mana.png", renderer);

  /* SPELLS TEXTURES */
  map[ID_BLEEDING] = new Texture("sangrado1.png", renderer);
  map[ID_BLEEDING_1] = new Texture("sangrado2.png", renderer);
  map[ID_BLEEDING_2] = new Texture("sangrado3.png", renderer);
  map[ID_BLEEDING_3] = new Texture("sangrado4.png", renderer);
  map[ID_BLEEDING_4] = new Texture("sangrado5.png", renderer);

  map[ID_MAGIC_ARROW] = new Texture("flecha_magica.png", renderer);

  map[ID_HEAL] = new Texture("curar.png", renderer);

  map[ID_ELECTRIC_SHOCK] = new Texture("descarga_electrica1.png", renderer);
  map[ID_ELECTRIC_SHOCK_1] = new Texture("descarga_electrica2.png", renderer);
  map[ID_ELECTRIC_SHOCK_2] = new Texture("descarga_electrica3.png", renderer);
  map[ID_ELECTRIC_SHOCK_3] = new Texture("descarga_electrica4.png", renderer);
  map[ID_ELECTRIC_SHOCK_4] = new Texture("descarga_electrica5.png", renderer);
  map[ID_ELECTRIC_SHOCK_5] = new Texture("descarga_electrica6.png", renderer);
  map[ID_ELECTRIC_SHOCK_6] = new Texture("descarga_electrica7.png", renderer);
  map[ID_ELECTRIC_SHOCK_7] = new Texture("descarga_electrica8.png", renderer);
  map[ID_ELECTRIC_SHOCK_8] = new Texture("descarga_electrica9.png", renderer);
  map[ID_ELECTRIC_SHOCK_9] = new Texture("descarga_electrica10.png", renderer);
  map[ID_ELECTRIC_SHOCK_10] = new Texture("descarga_electrica11.png", renderer);
  map[ID_ELECTRIC_SHOCK_11] = new Texture("descarga_electrica12.png", renderer);
  map[ID_ELECTRIC_SHOCK_12] = new Texture("descarga_electrica13.png", renderer);
  map[ID_ELECTRIC_SHOCK_13] = new Texture("descarga_electrica14.png", renderer);
  map[ID_ELECTRIC_SHOCK_14] = new Texture("descarga_electrica15.png", renderer);

  map[ID_EXPLOSION] = new Texture("explosion1.png", renderer);
  map[ID_EXPLOSION_1] = new Texture("explosion2.png", renderer);
  map[ID_EXPLOSION_2] = new Texture("explosion3.png", renderer);
  map[ID_EXPLOSION_3] = new Texture("explosion4.png", renderer);
  map[ID_EXPLOSION_4] = new Texture("explosion5.png", renderer);
  map[ID_EXPLOSION_5] = new Texture("explosion6.png", renderer);
  map[ID_EXPLOSION_6] = new Texture("explosion7.png", renderer);
  map[ID_EXPLOSION_7] = new Texture("explosion8.png", renderer);
  map[ID_EXPLOSION_8] = new Texture("explosion9.png", renderer);
  map[ID_EXPLOSION_9] = new Texture("explosion10.png", renderer);
  map[ID_EXPLOSION_10] = new Texture("explosion11.png", renderer);
  map[ID_EXPLOSION_11] = new Texture("explosion12.png", renderer);
  map[ID_EXPLOSION_12] = new Texture("explosion13.png", renderer);
  map[ID_EXPLOSION_13] = new Texture("explosion14.png", renderer);
  map[ID_EXPLOSION_14] = new Texture("explosion15.png", renderer);
  map[ID_EXPLOSION_15] = new Texture("explosion16.png", renderer);
  map[ID_EXPLOSION_16] = new Texture("explosion17.png", renderer);
  map[ID_EXPLOSION_17] = new Texture("explosion18.png", renderer);
  map[ID_EXPLOSION_18] = new Texture("explosion19.png", renderer);
  map[ID_EXPLOSION_19] = new Texture("explosion20.png", renderer);
  map[ID_EXPLOSION_20] = new Texture("explosion21.png", renderer);
}

TextureManager::~TextureManager() {}

Texture& TextureManager::get_texture(id_texture_t id) { return *map[id]; }

Texture& TextureManager::get_texture(id_texture_t id, int lifetime) {
  id_texture_t id_frame;

  switch (id) {
    case ID_BLEEDING:
      if (lifetime > FRAMES_PER_TEXTURE * 4)
        id_frame = id;
      else if (lifetime > FRAMES_PER_TEXTURE * 3)
        id_frame = (id_texture_t)(id + 1);
      else if (lifetime > FRAMES_PER_TEXTURE * 2)
        id_frame = (id_texture_t)(id + 2);
      else if (lifetime > FRAMES_PER_TEXTURE)
        id_frame = (id_texture_t)(id + 3);
      else
        id_frame = (id_texture_t)(id + 4);
      break;

    case ID_ELECTRIC_SHOCK:
      if (lifetime > FRAMES_PER_TEXTURE * 14)
        id_frame = id;
      else if (lifetime > FRAMES_PER_TEXTURE * 13)
        id_frame = (id_texture_t)(id + 1);
      else if (lifetime > FRAMES_PER_TEXTURE * 12)
        id_frame = (id_texture_t)(id + 2);
      else if (lifetime > FRAMES_PER_TEXTURE * 11)
        id_frame = (id_texture_t)(id + 3);
      else if (lifetime > FRAMES_PER_TEXTURE * 10)
        id_frame = (id_texture_t)(id + 4);
      else if (lifetime > FRAMES_PER_TEXTURE * 9)
        id_frame = (id_texture_t)(id + 5);
      else if (lifetime > FRAMES_PER_TEXTURE * 8)
        id_frame = (id_texture_t)(id + 6);
      else if (lifetime > FRAMES_PER_TEXTURE * 7)
        id_frame = (id_texture_t)(id + 7);
      else if (lifetime > FRAMES_PER_TEXTURE * 6)
        id_frame = (id_texture_t)(id + 8);
      else if (lifetime > FRAMES_PER_TEXTURE * 5)
        id_frame = (id_texture_t)(id + 9);
      else if (lifetime > FRAMES_PER_TEXTURE * 4)
        id_frame = (id_texture_t)(id + 10);
      else if (lifetime > FRAMES_PER_TEXTURE * 3)
        id_frame = (id_texture_t)(id + 11);
      else if (lifetime > FRAMES_PER_TEXTURE * 2)
        id_frame = (id_texture_t)(id + 12);
      else if (lifetime > FRAMES_PER_TEXTURE)
        id_frame = (id_texture_t)(id + 13);
      else
        id_frame = (id_texture_t)(id + 14);
      break;

    case ID_EXPLOSION:
      if (lifetime > FRAMES_PER_TEXTURE * 20)
        id_frame = id;
      else if (lifetime > FRAMES_PER_TEXTURE * 19)
        id_frame = (id_texture_t)(id + 1);
      else if (lifetime > FRAMES_PER_TEXTURE * 18)
        id_frame = (id_texture_t)(id + 2);
      else if (lifetime > FRAMES_PER_TEXTURE * 17)
        id_frame = (id_texture_t)(id + 3);
      else if (lifetime > FRAMES_PER_TEXTURE * 16)
        id_frame = (id_texture_t)(id + 4);
      else if (lifetime > FRAMES_PER_TEXTURE * 15)
        id_frame = (id_texture_t)(id + 5);
      else if (lifetime > FRAMES_PER_TEXTURE * 14)
        id_frame = (id_texture_t)(id + 6);
      else if (lifetime > FRAMES_PER_TEXTURE * 13)
        id_frame = (id_texture_t)(id + 7);
      else if (lifetime > FRAMES_PER_TEXTURE * 12)
        id_frame = (id_texture_t)(id + 8);
      else if (lifetime > FRAMES_PER_TEXTURE * 11)
        id_frame = (id_texture_t)(id + 9);
      else if (lifetime > FRAMES_PER_TEXTURE * 10)
        id_frame = (id_texture_t)(id + 10);
      else if (lifetime > FRAMES_PER_TEXTURE * 9)
        id_frame = (id_texture_t)(id + 11);
      else if (lifetime > FRAMES_PER_TEXTURE * 8)
        id_frame = (id_texture_t)(id + 12);
      else if (lifetime > FRAMES_PER_TEXTURE * 7)
        id_frame = (id_texture_t)(id + 13);
      else if (lifetime > FRAMES_PER_TEXTURE * 6)
        id_frame = (id_texture_t)(id + 14);
      else if (lifetime > FRAMES_PER_TEXTURE * 5)
        id_frame = (id_texture_t)(id + 15);
      else if (lifetime > FRAMES_PER_TEXTURE * 4)
        id_frame = (id_texture_t)(id + 16);
      else if (lifetime > FRAMES_PER_TEXTURE * 3)
        id_frame = (id_texture_t)(id + 17);
      else if (lifetime > FRAMES_PER_TEXTURE * 2)
        id_frame = (id_texture_t)(id + 18);
      else if (lifetime > FRAMES_PER_TEXTURE)
        id_frame = (id_texture_t)(id + 19);
      else
        id_frame = (id_texture_t)(id + 20);
      break;

    default:
      break;
  }

  return *map[id_frame];
}

void TextureManager::set_aspect_ratio(const float w_ratio,
                                      const float h_ratio) {
  width_ratio = w_ratio;
  height_ratio = h_ratio;
}

float TextureManager::get_w_ratio() const { return width_ratio; }

float TextureManager::get_h_ratio() const { return height_ratio; }