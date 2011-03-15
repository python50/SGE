#include "engine/engine.h"
#include "obj_gameobject.h"

game_object::game_object()
{
}

void game_object::update()
{
}

void game_object::move()
{
    if (move_mode==0)
        return;

    if (move_mode==1)
    {
        x+=xvol;
        y+=yvol;
        z+=zvol;
    }

    if (move_mode==2)
    {
        x+=drip_xlength(drip_radian(angle),speed);
        y+=drip_ylength(drip_radian(angle),speed);
    }
}

void game_object::init()
{
    start_x=x;
    start_y=y;
    start_z=z;
    xvol=0;
    yvol=0;
    zvol=0;
    start_angle=angle;
    self=resource::object.size()-1;
    var::sort_z=1;
}
void game_object::events()
{

}

void game_object::update_rect()
{
    rect.x=x;
    rect.y=y;
    rect.w=sprite->w;
    rect.h=sprite->h;
}


void game_object::call(string function,float num,string str)
{
}
void game_object::call(string function,float,float,float,bool)
{
}

void game_object::reset()
{
    x=start_x;
    y=start_y;
    z=start_z;
    angle=start_angle;
}

std::string game_object::get_type(int typen)
{
    if (typen==0)
        return type[0];
    if (typen==1)
        return type[1];
    if (typen==2)
        return type[2];

    return "";
}


SDL_Surface * game_object::get_sprite()
{
    return sprite;
}

SDL_Rect game_object::get_rect()
{
    return rect;
}
