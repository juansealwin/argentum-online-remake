#include "ui_status.h"

UIStatus::UIStatus() {
  inventory = Inventory();
  bank = Inventory();
  market = Inventory();
  text_messages.clear();
  second_inventory = false;
}

UIStatus::~UIStatus() {}

UIStatus& UIStatus::operator=(const UIStatus& other_status) {
  inventory = other_status.inventory;
  bank = other_status.bank;
  market = other_status.market;
  bank_or_market = other_status.bank_or_market;
  second_inventory = other_status.second_inventory;
  text_messages = other_status.text_messages;
  return *this;
}

void UIStatus::set_ui_messages(std::string name, int lvl, int max_hp, int hp,
                               int max_mn, int mn, int goal_xp, int xp,
                               int gold) {
  // Vaciamos el inventario anterior
  inventory = Inventory();

  // Le damos formato al nombre
  text_messages[NAME] = name;

  // Le damos formato al nivel
  std::ostringstream level_oss;
  level_oss << "Nivel " << lvl;
  text_messages[LEVEL] = level_oss.str();

  // Le damos formato a la experiencia (en porcentaje del total)
  std::ostringstream exp_oss;
  exp_oss << xp * 100 / goal_xp << " %";
  text_messages[EXP] = exp_oss.str();

  // Le damos formato a la experiencia
  std::ostringstream gold_oss;
  gold_oss << gold;
  text_messages[GOLD_QUANTITY] = gold_oss.str();

  // Le damos formato a la experiencia
  std::ostringstream health_oss;
  health_oss << hp << "/" << max_hp;
  text_messages[HEALTH] = health_oss.str();

  // Le damos formato a la experiencia
  std::ostringstream mana_oss;
  mana_oss << mn << "/" << max_mn;
  text_messages[MANA] = mana_oss.str();
}

void UIStatus::add_item(inventory_t inv_type, id_texture_t new_item, int slot) {
  switch (inv_type) {
    case INVENTORY:
      inventory.add_item(new_item, slot);
      break;

    // Los casos de abajo nunca van a ocurrir
    case BANK:
      bank.add_item(new_item, slot);
      break;

    case MARKET:
      market.add_item(new_item, slot);
      break;

    default:
      break;
  }
}

void UIStatus::add_item(inventory_t inv_type, id_texture_t new_item) {
  switch (inv_type) {
    case INVENTORY:
      inventory.add_item(new_item);
      break;

    case BANK:
      bank.add_item(new_item);
      break;

    case MARKET:
      market.add_item(new_item);
      break;

    default:
      break;
  }
}

void UIStatus::charge_messages(std::string msg1, std::string msg2,
                               std::string msg3, std::string msg4) {
  text_messages[MESSAGE_1] = msg1;
  text_messages[MESSAGE_2] = msg2;
  text_messages[MESSAGE_3] = msg3;
  text_messages[MESSAGE_4] = msg4;
}

void UIStatus::render(SDL_Renderer* renderer, std::string input_txt,
                      bool is_selected, int index) {
  // Renderizamos el UI estático
  texture_manager.get_texture(ID_UI).render(renderer, NULL, 0, 0);

  // Renderizamos los items del inventario
  inventory.render(renderer, is_selected, index);

  // Chequeamos si esta el mercado o banco abierto
  if (second_inventory) {
    if (bank_or_market == BANK)
      bank.render(renderer);
    else
      market.render(renderer);
  }

  // Creamos las nuevas cajas de texto con los mensajes/textos actualizados
  TextBox message1(MESSAGE_1, text_messages[MESSAGE_1]);
  TextBox message2(MESSAGE_2, text_messages[MESSAGE_2]);
  TextBox message3(MESSAGE_3, text_messages[MESSAGE_3]);
  TextBox message4(MESSAGE_4, text_messages[MESSAGE_4]);
  TextBox input_text(INPUT_TEXT, input_txt);
  TextBox level(LEVEL, text_messages[LEVEL]);
  TextBox name(NAME, text_messages[NAME]);
  TextBox exp(EXP, text_messages[EXP]);
  TextBox gold(GOLD_QUANTITY, text_messages[GOLD_QUANTITY]);
  TextBox health(HEALTH, text_messages[HEALTH]);
  TextBox mana(MANA, text_messages[MANA]);

  // Creamos las texturas a partir de los nuevos textos
  message1.set_texture(renderer);
  message2.set_texture(renderer);
  message3.set_texture(renderer);
  message4.set_texture(renderer);
  input_text.set_texture(renderer);
  level.set_texture(renderer);
  name.set_texture(renderer);
  exp.set_texture(renderer);
  gold.set_texture(renderer);
  health.set_texture(renderer);
  mana.set_texture(renderer);

  // Renderizamos cada caja de texto
  message1.render(renderer, 0, 0);
  message2.render(renderer, 0, 0);
  message3.render(renderer, 0, 0);
  message4.render(renderer, 0, 0);
  input_text.render(renderer, 0, 0);
  level.render(renderer, 0, 0);
  name.render(renderer, 0, 0);
  exp.render(renderer, 0, 0);
  gold.render(renderer, 0, 0);
  health.render(renderer, 0, 0);
  mana.render(renderer, 0, 0);
}

std::map<int, std::pair<id_texture_t, bool>> UIStatus::get_items() {
  return inventory.get_items();
}

std::map<int, std::pair<id_texture_t, bool>> UIStatus::get_shop() {
  return (bank_or_market == BANK) ? bank.get_items() : market.get_items();
}

bool UIStatus::is_shop_open(inventory_t& type) {
  type = bank_or_market;
  /*if (second_inventory == 0)
    std::cout << "NO ESTA ABIERTO" << std::endl;
  else if (second_inventory == 1)
    std::cout << " ESTA ABIERTO" << std::endl;
  else
    std::cout << "HAY BASURA" << std::endl;*/
  return second_inventory;
}

void UIStatus::open_shop(inventory_t type) {
  bank_or_market = type;
  second_inventory = true;
}

void UIStatus::close_shops() {
  bank = Inventory();
  market = Inventory();
  second_inventory = false;
}