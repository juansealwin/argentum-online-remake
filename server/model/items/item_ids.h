#ifndef ITEM_IDS_H
#define ITEM_IDS_H

typedef enum {
  turtle_shield = 1,
  iron_shield,
  hood,
  iron_helmet,
  magic_hat,
  leather_armour,
  plate_armour,
  blue_tunic,
  hp_potion,
  mana_potion,
  sword,
  axe,
  hammer,
  simple_bow,
  compound_bow,
  ash_stick,
  gnarled_staff,
  crimp_staff,
  elven_flute,
  //Actualizar esto si se agregan mas items!
  first_item_id = turtle_shield,
  last_item_id = elven_flute
} item_t;

#endif //ITEM_IDS_H