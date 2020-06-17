#ifndef ENTITY_H
#define ENTITY_H

class Entity {
 public:
  Entity(int x, int y, int type, char repr);
  Entity(const Entity &) = delete;
  virtual ~Entity();
  virtual char char_representation();
  virtual void set_x_y_position(int x, int y);
  virtual int get_type();
  virtual void update() = 0;
  int x_position;
  int y_position;


 private:
  int type;
  char representation;
};

#endif  // ENTITY_H
