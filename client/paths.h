#ifndef PATHS_H
#define PATHS_H

#include <map>
#include <string>
#include "types.h"

class Paths {
 private:
  static Paths* instance_paths;
  Paths();
  std::map<id_texture_t, std::string> map_paths;

 public:
  static Paths* get_instance();
  ~Paths();
  const char* get_path_texture(id_texture_t);
};

extern Paths* paths;// = Paths::get_instance();

#endif
