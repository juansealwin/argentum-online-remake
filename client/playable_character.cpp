#include "playable_character.h"

PlayableCharacter::PlayableCharacter(entity_t id_char, int new_x, int new_y,
                                     move_t orient, bool ghost_mod,
                                     id_texture_t new_helmet,
                                     id_texture_t new_armor,
                                     id_texture_t new_shield,
                                     id_texture_t new_weapon) {
  x = new_x;
  y = new_y;
  orientation = orient;
  set_character_features(id_char);
  set_head_dimensions(id_char);
  animation_move = Animation(width, height, type_character);
  std::vector<sound_t> borr;
  update_equipment(ghost_mod, false, new_helmet, new_armor, new_shield,
                   new_weapon, borr);
}

PlayableCharacter::PlayableCharacter(const PlayableCharacter& other_pc) {
  /** Copiamos la parte de Drawable **/
  x = other_pc.x;
  y = other_pc.y;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;

  /** Copiamos la parte de Character **/
  type_character = other_pc.type_character;
  animation_move = other_pc.animation_move;
  orientation = other_pc.orientation;
  body_rect = other_pc.body_rect;
  walk = other_pc.walk;
  spellbound = other_pc.spellbound;

  /** Copiamos la parte de PlayableCharacter **/
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;
  zen_mode = other_pc.zen_mode;
  if (zen_mode) {
    meditating_frame = other_pc.meditating_frame;
    meditating_animation = other_pc.meditating_animation;
  }
  ghost = other_pc.ghost;
  if (ghost) {
    ghost_body = other_pc.ghost_body;
    ghost_frame = other_pc.ghost_frame;
  }
  // Copiamos las animaciones y los frames solo si tienen equipado el item
  helmet = other_pc.helmet;
  if (helmet != ID_NULL) frame_equipped_h = other_pc.frame_equipped_h;
  armor = other_pc.armor;
  if (armor != ID_NULL) {
    armor_animation = other_pc.armor_animation;
    frame_equipped_a = other_pc.frame_equipped_a;
  }
  shield = other_pc.shield;
  if (shield != ID_NULL) {
    shield_animation = other_pc.shield_animation;
    frame_equipped_s = other_pc.frame_equipped_s;
  }
  weapon = other_pc.weapon;
  if (weapon != ID_NULL) {
    weapon_animation = other_pc.weapon_animation;
    frame_equipped_w = other_pc.frame_equipped_w;
  }
}

PlayableCharacter& PlayableCharacter::operator=(
    const PlayableCharacter& other_pc) {
  /** Copiamos la parte de Drawable **/
  x = other_pc.x;
  y = other_pc.y;
  // Colocamos las dimensiones del personaje
  width = other_pc.width;
  height = other_pc.height;

  /** Copiamos la parte de Character **/
  type_character = other_pc.type_character;
  orientation = other_pc.orientation;
  animation_move = other_pc.animation_move;
  body_rect = other_pc.body_rect;
  walk = other_pc.walk;
  spellbound = other_pc.spellbound;

  /** Copiamos la parte de PlayableCharacter **/
  // Colocamos las dimensiones de su cabeza
  type_head = other_pc.type_head;
  head_rect = other_pc.head_rect;
  zen_mode = other_pc.zen_mode;
  if (zen_mode) {
    meditating_frame = other_pc.meditating_frame;
    meditating_animation = other_pc.meditating_animation;
  }
  ghost = other_pc.ghost;
  if (ghost) {
    ghost_body = other_pc.ghost_body;
    ghost_frame = other_pc.ghost_frame;
  }
  // Copiamos las animaciones y los frames solo si tienen equipado el item
  helmet = other_pc.helmet;
  if (helmet != ID_NULL) frame_equipped_h = other_pc.frame_equipped_h;
  armor = other_pc.armor;
  if (armor != ID_NULL) {
    armor_animation = other_pc.armor_animation;
    frame_equipped_a = other_pc.frame_equipped_a;
  }
  shield = other_pc.shield;
  if (shield != ID_NULL) {
    shield_animation = other_pc.shield_animation;
    frame_equipped_s = other_pc.frame_equipped_s;
  }
  weapon = other_pc.weapon;
  if (weapon != ID_NULL) {
    weapon_animation = other_pc.weapon_animation;
    frame_equipped_w = other_pc.frame_equipped_w;
  }
  return *this;
}

PlayableCharacter::~PlayableCharacter() {}

void PlayableCharacter::move(move_t move_type) {
  // Vemos que frame queremos dependiendo de si esta en modo fantasma
  if (ghost) {
    ghost_body = ghost_frame.get_next_clip(move_type);
  } else {
    body_rect = animation_move.get_next_clip(move_type);
    // Si tenemos algun arma equipada actualizamos su animacion
    if (armor != ID_NULL)
      frame_equipped_a = armor_animation.get_next_clip(move_type);
    if (shield != ID_NULL)
      frame_equipped_s = shield_animation.get_next_clip(move_type);
    if (weapon != ID_NULL)
      frame_equipped_w = weapon_animation.get_next_clip(move_type);
  }
  // A los jugables hay que actualizarles el perfil
  update_face_profile(move_type);
}

void PlayableCharacter::update_face_profile(move_t move_type) {
  // La cabeza del fantasma coincide
  head_rect.x = move_type * head_rect.w;
  // Si tiene un caso quipado tambien actualizamos el frame
  if (helmet != ID_NULL && !ghost)
    frame_equipped_h.x = move_type * frame_equipped_h.w;
}

void PlayableCharacter::render(SDL_Renderer* renderer, int x_rel, int y_rel) {
  // Si esta muerto lo renderizamos en modo fantasma
  if (ghost) {
    texture_manager.get_texture(ID_CORPSE).render(
        renderer, &ghost_body, x - x_rel, y - GHOST_HEIGHT / 2 - y_rel);

    // El 3 es para corregir la cabeza que no coincide EXACTAMENTE
    texture_manager.get_texture(ID_CORPSE_HEAD)
        .render(renderer, &head_rect, x + head_rect.w / 4 - x_rel + 2,
                y - GHOST_HEIGHT / 2 - head_rect.h / 2 - y_rel);
  } else {
    // Solo se renderiza la armadura o el cuerpo para no repetir manos y pies
    int offset = 0;
    // Esto se debe a que el gráfico de gnomo y enano esta desfasado
    if (type_character == ID_GNOME || type_character == ID_DWARF) offset = 10;
    if (armor != ID_NULL) {
      texture_manager.get_texture(armor).render(
          renderer, &frame_equipped_a, x - x_rel,
          y - height / 2 - offset - y_rel);
    } else {
      texture_manager.get_texture(type_character)
          .render(renderer, &body_rect, x - x_rel,
                  y - height / 2 - offset - y_rel);
    }
    // Renderizamos cabeza
    texture_manager.get_texture(type_head).render(
        renderer, &head_rect, x + head_rect.w / 4 - x_rel,
        y - height / 2 - head_rect.h / 2 - y_rel);

    // Si tiene el casco equipado lo renderizamos
    if (helmet != ID_NULL) {
      int offset_y = 0;
      // Los gorros tienen un offset
      if (helmet == ID_MAGIC_HAT_EQUIPPED) offset_y = head_rect.h;
      texture_manager.get_texture(helmet).render(
          renderer, &frame_equipped_h, x + head_rect.w / 4 - x_rel,
          y - height / 2 - head_rect.h / 2 - y_rel - offset_y);
    }

    // Si tiene el escudo equipado lo renderizamos
    if (shield != ID_NULL) {
      texture_manager.get_texture(shield).render(
          renderer, &frame_equipped_s, x - x_rel, y - height / 2 - y_rel);
    }

    // Si tiene el arma equipada la renderizamos
    if (weapon != ID_NULL) {
      texture_manager.get_texture(weapon).render(
          renderer, &frame_equipped_w, x - x_rel, y - height * 3 / 5 - y_rel);
    }

    // Si esta afectado por algún hechizo lo renderizamos
    if (spellbound.spell_alive())
      spellbound.render(renderer, x - x_rel, y - height / 2 - y_rel);

    // Si esta meditando renderizamos la meditación
    if (zen_mode)
      texture_manager.get_texture(ID_MEDITATION)
          .render(renderer, &meditating_frame, x - x_rel, y - height - y_rel);
  }
}

void PlayableCharacter::set_head_dimensions(entity_t id) {
  switch (id) {
    case HUMAN:
      head_rect = {0, 0, 17, 16};
      type_head = ID_HUMAN_HEAD;
      break;

    case ELF:
      head_rect = {0, 0, 17, 16};
      type_head = ID_ELF_HEAD;
      break;

    case GNOME:
      head_rect = {0, 0, 17, 17};
      type_head = ID_GNOME_HEAD;
      break;

    case DWARF:
      head_rect = {0, 0, 17, 17};
      type_head = ID_DWARF_HEAD;
      break;

    default:
      head_rect = {0, 0, 0, 0};
      type_head = ID_NULL;
      break;
  }
}

void PlayableCharacter::unequip_item(equipped_t item) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (item) {
    case HELMET:
      helmet = ID_NULL;
      break;

    case ARMOR:
      armor = ID_NULL;
      break;

    case SHIELD:
      shield = ID_NULL;
      break;

    case WEAPON:
      weapon = ID_NULL;
      break;

    default:
      break;
  }
}

void PlayableCharacter::equip_item(equipped_t item, id_texture_t id) {
  // Reinicializamos el item para que no tenga valores dentro
  switch (item) {
    case HELMET:
      set_item_dimensions(id);
      break;

    case ARMOR:
      set_item_dimensions(id);
      break;

    case SHIELD:
      set_item_dimensions(id);
      break;

    case WEAPON:
      set_item_dimensions(id);
      break;

    default:
      break;
  }
}

void PlayableCharacter::update_equipment(bool ghost_mod, bool meditating,
                                         id_texture_t new_helmet,
                                         id_texture_t new_armor,
                                         id_texture_t new_shield,
                                         id_texture_t new_weapon,
                                         std::vector<sound_t>& next_sounds) {
  // Chequeamos si el personaje murió
  if (!ghost && ghost_mod) {
    ghost = ghost_mod;
    ghost_frame = Animation(GHOST_WIDTH, GHOST_HEIGHT, ID_CORPSE);
    ghost_body = {0, 0, GHOST_WIDTH, GHOST_HEIGHT};
    next_sounds.push_back(DEAD_PC);
  } else {
    // Chequeamos si revivio
    if (ghost && !ghost_mod) {
      ghost = ghost_mod;
      next_sounds.push_back(CAST_REVIVE);
    }

    // Seteamos si el personaje esta meditando
    if (meditating && !zen_mode) {
      zen_mode = meditating;
      meditating_animation = Animation(ZEN_WIDTH, ZEN_HEIGHT, ID_MEDITATION);
      meditating_frame = {0, 0, ZEN_WIDTH, ZEN_HEIGHT};
    }

    // Chequeamos si dejo de meditar
    else if (!meditating && zen_mode)
      zen_mode = meditating;

    // Chequeamos si sigue meditando
    else if (zen_mode && meditating) {
      meditating_frame = meditating_animation.get_next_clip();
      next_sounds.push_back(CAST_MEDITATION);
    }

    // Chequeamos si cambio el caso
    if (new_helmet == ID_NULL && helmet != ID_NULL)
      unequip_item(HELMET);
    else if (new_helmet != ID_NULL && helmet == ID_NULL)
      equip_item(HELMET, new_helmet);
    else if (new_helmet != helmet)
      equip_item(HELMET, new_helmet);

    // Chequeamos si cambio la armadura
    if (new_armor == ID_NULL && armor != ID_NULL)
      unequip_item(ARMOR);
    else if (new_armor != ID_NULL && armor == ID_NULL)
      equip_item(ARMOR, new_armor);
    else if (new_armor != armor)
      equip_item(ARMOR, new_armor);

    // Chequeamos si cambio el escudo
    if (new_shield == ID_NULL && shield != ID_NULL)
      unequip_item(SHIELD);
    else if (new_shield != ID_NULL && shield == ID_NULL)
      equip_item(SHIELD, new_shield);
    else if (new_shield != shield)
      equip_item(SHIELD, new_shield);

    // Chequeamos si hubo algun cambio el arma
    if (new_weapon == ID_NULL && weapon != ID_NULL)
      unequip_item(WEAPON);
    else if (new_weapon != ID_NULL && weapon == ID_NULL)
      equip_item(WEAPON, new_weapon);
    else if (new_weapon != weapon)
      equip_item(WEAPON, new_weapon);
  }
}

void PlayableCharacter::set_item_dimensions(id_texture_t id) {
  switch (id) {
    // Armas
    case ID_SWORD:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 48};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_SWORD_EQUIPPED;
      break;

    case ID_AXE:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 48};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_AXE_EQUIPPED;
      break;

    case ID_HAMMER:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 48};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_HAMMER_EQUIPPED;
      break;

    case ID_ASH_STICK:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 48};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_ASH_STICK_EQUIPPED;
      break;

    case ID_ELVEN_ELUDE:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_ELVEN_ELUDE_EQUIPPED;
      break;

    case ID_KNOTTY_STAFF:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_KNOTTY_STAFF_EQUIPPED;
      break;

    case ID_CRIMPED_STAFF:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_CRIMPED_STAFF_EQUIPPED;
      break;

    case ID_DEADLY_STAFF:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_DEADLY_STAFF_EQUIPPED;
      break;

    case ID_SIMPLE_BOW:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_SIMPLE_BOW_EQUIPPED;
      break;

    case ID_COMPOUND_BOW:
      frame_equipped_w = {body_rect.x, body_rect.y, 25, 45};
      weapon_animation = Animation(frame_equipped_w.w, frame_equipped_w.h);
      weapon = ID_COMPOUND_BOW_EQUIPPED;
      break;

    // Escudos
    case ID_IRON_SHIELD:
      frame_equipped_s = {body_rect.x, body_rect.y, 25, 45};
      shield_animation = Animation(frame_equipped_s.w, frame_equipped_s.h);
      shield = ID_IRON_SHIELD_EQUIPPED;
      break;

    case ID_TURTLE_SHIELD:
      frame_equipped_s = {body_rect.x, body_rect.y, 25, 45};
      shield_animation = Animation(frame_equipped_s.w, frame_equipped_s.h);
      shield = ID_TURTLE_SHIELD_EQUIPPED;
      break;

    // Cascos y sombreros
    case ID_MAGIC_HAT:
      frame_equipped_h = {head_rect.x, 0, 17, 19};
      helmet = ID_MAGIC_HAT_EQUIPPED;
      break;

    case ID_HOOD:
      frame_equipped_h = {head_rect.x, 0, 17, 18};
      helmet = ID_HOOD_EQUIPPED;
      break;

    case ID_IRON_HELMET:
      frame_equipped_h = {head_rect.x, 0, 17, 18};
      helmet = ID_IRON_HELMET_EQUIPPED;
      break;

    // Armaduras y vestimentas
    case ID_LEATHER_ARMOR:
      // El frame es el mismo para ambas texturas
      frame_equipped_a = {body_rect.x, body_rect.y, 25, 45};
      armor_animation = Animation(frame_equipped_a.w, frame_equipped_a.h);
      if (type_character == ID_GNOME || type_character == ID_DWARF)
        armor = ID_LEATHER_ARMOR_XS_EQUIPPED;
      else
        armor = ID_LEATHER_ARMOR_EQUIPPED;
      break;

    case ID_PLATE_ARMOR:
      // El frame es el mismo para ambas texturas
      frame_equipped_a = {body_rect.x, body_rect.y, 25, 45};
      armor_animation = Animation(frame_equipped_a.w, frame_equipped_a.h);
      if (type_character == ID_GNOME || type_character == ID_DWARF)
        armor = ID_PLATE_ARMOR_XS_EQUIPPED;
      else
        armor = ID_PLATE_ARMOR_EQUIPPED;
      break;

    case ID_BLUE_TUNIC:
      frame_equipped_a = {body_rect.x, body_rect.y, 25, 45};
      armor_animation = Animation(frame_equipped_a.w, frame_equipped_a.h);
      if (type_character == ID_GNOME || type_character == ID_DWARF)
        armor = ID_BLUE_TUNIC_XS_EQUIPPED;
      else
        armor = ID_BLUE_TUNIC_EQUIPPED;
      break;

    default:
      armor = ID_NULL;
      break;
  }
}