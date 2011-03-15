#ifndef OBJ_GAMEOBJECT_H_INCLUDED
#define OBJ_GAMEOBJECT_H_INCLUDED

#include "engine/engine.h"

class game_object
{
    //object(float xx,float yy,int zz,unsigned int image_num);

    public:

    SDL_Surface* sprite;
    SDL_Rect rect;
    std::string type[3];// name , group , controller

    unsigned int self;
    bool visible; // draw ?
    bool solid; // check for collisions ?
    bool remove; // kill it ?
    bool center; // draw sprite centered ?

    int   move_mode;
    float angle;
    float speed;
    float x;
    float y;
    float z;
    float xvol;
    float yvol;
    float zvol;

    float start_angle;
    float start_x;
    float start_y;
    float start_z;

    game_object();

    virtual void init();

    virtual void update();

    virtual void move();

    virtual void events();
    virtual void update_rect();

    virtual void call(string function,float num,string str) ;
    virtual void call(string function,float,float,float,bool) ;

    virtual void reset();

    std::string get_type(int typen);

    SDL_Surface * get_sprite();

    SDL_Rect get_rect();

};


#endif // OBJ_GAMEOBJECT_H_INCLUDED
