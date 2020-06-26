#include "serializer.h"
#include <vector>
template <typename T>
T extract(const std::vector<unsigned char> &v, int pos)
{
  T value;
  memcpy(&value, &v[pos], sizeof(T));
  return value;
}

std::vector<unsigned char> Serializer::serialize_game_status(ArgentumGame *game) {

  //serializacion actual:
  //<uint8_t>(notification id),<uint16_t>(id unico por entidad), <uint8_t>(id del tipo de entidad), <uint8_t>(pos x), <uint8_t>(pos y), ....
  std::vector<unsigned char> serialization;
  uint8_t notification_id = 1;
  serialization.push_back(notification_id);
  for (auto &entity : game->entities) {
    uint16_t entity_id = htons(entity.first);
    unsigned int current_pos = serialization.size();
    serialization.resize(serialization.size() + sizeof(entity_id));
    std::memcpy(serialization.data() + current_pos, &entity_id, sizeof(entity_id));
    uint8_t entity_type = entity.second->type;
    uint8_t x = entity.second->x_position;
    uint8_t y = entity.second->y_position;
    serialization.push_back(entity_type);
    serialization.push_back(x);
    serialization.push_back(y);
  }
  
  //debug_deserialize(serialization);
  return serialization;
}

void Serializer::debug_deserialize(std::vector<unsigned char> serialization) {
  std::cout << "vector size is " << serialization.size() << std::endl;
  // uint16_t id = ntohs(extract<uint16_t>(serialization, 21)); 
  // int entity_type = (int)serialization.at(23);
  // int x = (int)serialization.at(24);
  // int y = (int)serialization.at(25);
  // std::cout << "Entity id: " << id << ", type: " << entity_type << ", x_pos: " << x << ", y_pos: " << y << std::endl;
  
  // for (int i = 1; i < serialization.size(); i++) {
  //   std::cout << "Vector at pos " << i << ": " << (int)serialization[i] <<
  //   std::endl;
  // }
  int j = 1;
  while (j < serialization.size()) {
    uint16_t id = ntohs(extract<uint16_t>(serialization, j));
    j += 2;
    int entity_type = (int)serialization.at(j);
    j++;
    int x = (int)serialization.at(j);
    j++;
    int y = (int)serialization.at(j);
    std::cout << "Entity id: " << id << ", type: " << entity_type << ", x_pos: " << x << ", y_pos: " << y << std::endl;
    j++;
  }


  // for (int i = 1; i < serialization.size(); i++) {
  //   std::cout << "Vector at pos " << i << ": " << (int)serialization[i] <<
  //   std::endl;
  // }
}