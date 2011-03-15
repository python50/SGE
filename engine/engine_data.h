#ifndef ENGINE_DATA_H_INCLUDED
#define ENGINE_DATA_H_INCLUDED

#include "engine/engine.h"
#include "object/obj_gameobject.h"

#include <vector>

namespace resource
{
    extern vector< ::game_object*> object;
    extern vector<SDL_Surface*> image;
    extern vector<TTF_Font*> font;
    extern vector<Mix_Chunk*> sound;
    extern vector<Mix_Music*> music;

    extern vector<string> object_id;
    extern vector<string> image_id;
    extern vector<string> font_id;
    extern vector<string> sound_id;
    extern vector<string> music_id;
}
namespace var
{
    // gameplay

    extern int display_fps;
    extern int current_fps;
    extern long current_ticks;
    extern long last_ticks;
    extern long last_update;
    extern long tick_delay;

    extern bool sort_z;

    // settings

    extern bool quit;
    extern bool pause;

    extern int sound_volume;
    extern int music_volume;

    extern string error[2];
    extern int errorlevel;

    extern SDL_Joystick *joystick;
    extern bool joystick_enable;
    extern bool fps_enable;

    // screen

    extern int x;
    extern int y;
    extern int width;
    extern int height;

    // map

    extern int map_number;
    extern string map_name;
    extern string map_author;
    extern string map_description;
    extern string map_difficulty;
    extern string map_date;
    extern int map_width;
    extern int map_height;

    // misc

    extern string data_dir;
    extern SDL_PixelFormat * format;
    extern SDL_Event event;

    extern int lives;
}

#endif // ENGINE_DATA_H_INCLUDED
