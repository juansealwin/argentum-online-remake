#ifndef TYPES_H
#define TYPES_H

typedef enum {
  ID_HUMAN = 0,
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
  ID_MAP_GRASS,
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
  PRIEST
} character_t;

typedef enum {
  MOVE_DOWN = 0,
  MOVE_UP = 3,
  MOVE_LEFT = 2,
  MOVE_RIGHT = 1
} move_t;

#endif