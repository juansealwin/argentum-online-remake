#ifndef TYPES_H
#define TYPES_H

#define FRAMES_ELECTRIC_SHOCK 15
#define FRAMES_EXPLOSION 21
#define FRAMES_BLEEDING 5
#define FRAMES_HEAL 10
#define FRAMES_MAGIC_ARROW 8
#define FRAMES_PER_TEXTURE 6

typedef enum {
  ID_NULL = 0,
  ID_UI,
  ID_SELECTOR,
  ID_ITEM_EQUIPPED,
  ID_MEDITATION,
  ID_CORPSE,
  ID_CORPSE_HEAD,
  ID_HUMAN,
  ID_HUMAN_HEAD,
  ID_ELF,
  ID_ELF_HEAD,
  ID_GNOME,
  ID_GNOME_HEAD,
  ID_DWARF,
  ID_DWARF_HEAD,
  ID_SPIDER,
  ID_SKELETON,
  ID_GOBLIN,
  ID_ZOMBIE,
  ID_PRIEST,
  ID_MERCHANT,
  ID_BANKER,
  ID_MAP_GRASS_BACKGROUND,
  ID_MAP_GRASS_OBJECTS,
  ID_MAP_DESERT_BACKGROUND,
  ID_MAP_DESERT_OBJECTS,
  ID_MAP_ARGAL_BACKGROUND,
  ID_MAP_ARGAL_OBJECTS,
  ID_GOLD,
  ID_HP_POTION,
  ID_MANA_POTION,
  ID_SWORD,
  ID_SWORD_EQUIPPED,
  ID_AXE,
  ID_AXE_EQUIPPED,
  ID_HAMMER,
  ID_HAMMER_EQUIPPED,
  ID_ASH_STICK,
  ID_ASH_STICK_EQUIPPED,
  ID_KNOTTY_STAFF,
  ID_KNOTTY_STAFF_EQUIPPED,
  ID_CRIMPED_STAFF,
  ID_CRIMPED_STAFF_EQUIPPED,
  ID_ELVEN_ELUDE,
  ID_ELVEN_ELUDE_EQUIPPED,
  ID_SIMPLE_BOW,
  ID_SIMPLE_BOW_EQUIPPED,
  ID_COMPOUND_BOW,
  ID_COMPOUND_BOW_EQUIPPED,
  ID_IRON_SHIELD,
  ID_IRON_SHIELD_EQUIPPED,
  ID_TURTLE_SHIELD,
  ID_TURTLE_SHIELD_EQUIPPED,
  ID_MAGIC_HAT,
  ID_MAGIC_HAT_EQUIPPED,
  ID_HOOD,
  ID_HOOD_EQUIPPED,
  ID_IRON_HELMET,
  ID_IRON_HELMET_EQUIPPED,
  ID_LEATHER_ARMOR,
  ID_LEATHER_ARMOR_EQUIPPED,
  ID_LEATHER_ARMOR_XS_EQUIPPED,
  ID_PLATE_ARMOR,
  ID_PLATE_ARMOR_EQUIPPED,
  ID_PLATE_ARMOR_XS_EQUIPPED,
  ID_BLUE_TUNIC,
  ID_BLUE_TUNIC_EQUIPPED,
  ID_BLUE_TUNIC_XS_EQUIPPED,
  ID_BLEEDING,
  ID_BLEEDING_1,
  ID_BLEEDING_2,
  ID_BLEEDING_3,
  ID_BLEEDING_4,
  ID_MAGIC_ARROW,
  ID_HEAL,
  ID_ELECTRIC_SHOCK,
  ID_ELECTRIC_SHOCK_1,
  ID_ELECTRIC_SHOCK_2,
  ID_ELECTRIC_SHOCK_3,
  ID_ELECTRIC_SHOCK_4,
  ID_ELECTRIC_SHOCK_5,
  ID_ELECTRIC_SHOCK_6,
  ID_ELECTRIC_SHOCK_7,
  ID_ELECTRIC_SHOCK_8,
  ID_ELECTRIC_SHOCK_9,
  ID_ELECTRIC_SHOCK_10,
  ID_ELECTRIC_SHOCK_11,
  ID_ELECTRIC_SHOCK_12,
  ID_ELECTRIC_SHOCK_13,
  ID_ELECTRIC_SHOCK_14,
  ID_EXPLOSION,
  ID_EXPLOSION_1,
  ID_EXPLOSION_2,
  ID_EXPLOSION_3,
  ID_EXPLOSION_4,
  ID_EXPLOSION_5,
  ID_EXPLOSION_6,
  ID_EXPLOSION_7,
  ID_EXPLOSION_8,
  ID_EXPLOSION_9,
  ID_EXPLOSION_10,
  ID_EXPLOSION_11,
  ID_EXPLOSION_12,
  ID_EXPLOSION_13,
  ID_EXPLOSION_14,
  ID_EXPLOSION_15,
  ID_EXPLOSION_16,
  ID_EXPLOSION_17,
  ID_EXPLOSION_18,
  ID_EXPLOSION_19,
  ID_EXPLOSION_20
} id_texture_t;

typedef enum {
  HUMAN = 0,
  ELF,
  GNOME,
  DWARF,
  SPIDER,
  GOBLIN,
  ZOMBIE,
  SKELETON,
  MERCHANT,
  BANKER,
  PRIEST,
  ITEM
} entity_t;

typedef enum {
  MOVE_DOWN = 0,
  MOVE_UP = 3,
  MOVE_LEFT = 2,
  MOVE_RIGHT = 1
} move_t;

typedef enum {
  EVENT_NONE = 0,
  EVENT_QUIT,
  EVENT_SELECT_ITEM,
  EVENT_MESSAGE
} event_t;

typedef enum {
  DUMMY_ITEM,
  TURTLE_SHIELD,
  IRON_SHIELD,
  HOOD,
  IRON_HELMET,
  MAGIC_HAT,
  LEATHER_ARMOR,
  PLATE_ARMOR,
  BLUE_TUNIC,
  HP_POTION,
  MANA_POTION,
  SWORD,
  AXE,
  HAMMER,
  SIMPLE_BOW,
  COMPOUND_BOW,
  ASH_STICK,
  GNARLED_STAFF,
  CRIMP_STAFF,
  ELVEN_FLUTE,
  GOLD = 36
} item_t;

typedef enum { CURRENT_MAP, GRASS_MAP, DESERT_MAP, ARGAL_MAP } map_t;

typedef enum { HELMET, ARMOR, SHIELD, WEAPON } equipped_t;

typedef enum {
  MESSAGE_1,
  MESSAGE_2,
  MESSAGE_3,
  MESSAGE_4,
  INPUT_TEXT,
  NAME,
  LEVEL,
  EXP,
  GOLD_QUANTITY,
  HEALTH,
  MANA,
  USER,
  PASSWORD,
  RACE_MSG,
  CLASS_MSG
} text_box_t;

typedef enum { INVENTORY, BANK, MARKET } inventory_t;

typedef enum {
  BG_MUSIC_1,
  WALK_PC,
  WALK_SPIDER,
  WALK_SKELETON,
  WALK_GOBLIN,
  WALK_ZOMBIE,
  CAST_BLEEDING,
  CAST_MAGIC_ARROW,
  CAST_HEAL,
  CAST_ELECTRIC_SHOCK,
  CAST_EXPLOSION,
  CAST_REVIVE,
  CAST_MEDITATION,
  DEAD_PC
} sound_t;

#endif