#ifndef PATHS_H
#define PATHS_H

#include <string>
#include <map>

#define ID_HUMAN 0
#define ID_HUMAN_HEAD 1
#define ID_ELF 2
#define ID_ELF_HEAD 3
#define ID_GNOME 4
#define ID_GNOME_HEAD 5
#define ID_DWARF 6
#define ID_DWARF_HEAD 7
#define ID_SPIDER 8
#define ID_SKELETON 9
#define ID_GOBLIN 10
#define ID_ZOMBIE 11
#define ID_PRIEST 12
#define ID_MERCHANT 13
#define ID_BANKER 14
#define ID_MAP_GRASS 15

class Paths {
 private:
  std::map<int, std::string> map_paths;

 public:
  Paths();
  ~Paths();
  const char* getPathTexture(int);
};



#endif
