/*
 * Copyright (c) 2010, Jason White <whitewaterssoftwareinfo@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of White Waters Software (Jason White) nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL White Waters Software BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 ** Objects.h
 **
 ** This file contains declarations for all classes , may change !!!
 **
 **/

#include "engine/engine.h"
#include "object/obj_gameobject.h"

#include <vector>

#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

using namespace std;

game_object * game();
/*
namespace var
{
    extern vector< ::game_object*> _object_;
    extern vector<SDL_Surface*> _img_;
    extern vector<TTF_Font*> _font_;
    extern vector<Mix_Chunk*> _sound_;
    extern vector<Mix_Music*> _music_;

    extern vector<string> _object_id_;
    extern vector<string> _img_id_;
    extern vector<string> _font_id_;
    extern vector<string> _sound_id_;
    extern vector<string> _music_id_;

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
}*/

class hud_object : public game_object
{
    public:

    float off_x;
    float off_y;

    virtual void update_pos();

};

/// objects

class hud_text : public hud_object
{
    public:

    string text;
    float num;
    string ltext;
    float lnum;

    hud_text(float off_xx,float off_yy,float zz,string text,float num,unsigned int fontn);

    virtual void update();

    virtual void call(string function,float num=0,string str="");

    virtual void set_text(string text);
    virtual void set_num(float num);

};

class tile : public game_object
{
    public:

    tile(float xx,float yy,float zz,unsigned int image_num);

};

class brick : public game_object
{
    public:

    brick(float xx,float yy,float zz,unsigned int image_num,int typen);

    virtual void update();

};

class ball : public game_object
{
    public:

    ball(float xx,float yy,float zz,int typen);

    virtual void update();

};

class  player : public game_object
{
    public:

    player(float xx,float yy,float zz);

    virtual void events();
    virtual void update();

};



#endif // OBJECTS_H_INCLUDED

