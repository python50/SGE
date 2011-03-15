#include "engine/engine.h"

namespace resource
{
    vector<game_object*> object;
    vector<SDL_Surface*> image;
    vector<TTF_Font*> font;
    vector<Mix_Chunk*> sound;
    vector<Mix_Music*> music;

    vector<string> object_id;
    vector<string> image_id;
    vector<string> font_id;
    vector<string> sound_id;
    vector<string> music_id;
}
namespace var
{
    // gameplay

    int display_fps=0;
    int current_fps=0;
    long current_ticks=0;
    long last_ticks=0;
    long last_update=0;
    long tick_delay=0;

    bool sort_z=0;

    // settings

    bool quit=0;
    bool pause=0;

    int sound_volume=0;
    int music_volume=0;

    SDL_Joystick *joystick;
    bool joystick_enable=0;
    bool fps_enable=0;

    string error[2]= {""};

    int errorlevel=0;

    // screen

    int x=0;
    int y=0;
    int width=0;
    int height=0;

    // map

    int map_number=0;
    string map_name="";
    string map_author="";
    string map_description="";
    string map_difficulty="";
    string map_date="";
    int map_width=0;
    int map_height=0;

    // misc

    string data_dir="";
    SDL_PixelFormat * format;
    SDL_Event event;

    int lives;
}
