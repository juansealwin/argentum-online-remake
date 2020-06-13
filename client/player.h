#ifndef Player_H
#define Player_H

#include <string>
#include <vector>

#include "move.h"

class Player {
   protected:
    /*
    std::string user_name;
    std::string password;
    std::string id;
    std::string path_face_character;
    std::string path_body_character;
    */
    Move* animation_move = NULL;
    int body_w;
    int body_h;
    int head_w;
    int head_h;
    int total_clips = 6;

   public:
    Player();
    ~Player();
    SDL_Rect move(move_t);
    SDL_Rect getFaceProfile(move_t);
    int getBodyW();
    int getBodyH();
    int getHeadW();
    int getHeadH();
};

#endif