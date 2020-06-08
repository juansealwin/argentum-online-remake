#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class player {
  private:
    std::string user_name;
    std::string password;
    std::string id;
    std::string path_face_character;
    std::string path_body_character;


  public:
    player();
    ~player();

};

#endif