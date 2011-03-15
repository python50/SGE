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
 ** Objects.cpp
 **
 ** This file contains all of the objects for now , it may be spit up further
 **
 **/

#include <cstdio>
#include <vector>
//#include <iostream>
//#include <string>

#include "engine/engine.h"

using namespace std;

//class game_object;
/*
namespace var
{
    vector<game_object*> _object_;
    vector<SDL_Surface*> _img_;
    vector<TTF_Font*> _font_;
    vector<Mix_Chunk*> _sound_;
    vector<Mix_Music*> _music_;

    vector<string> _object_id_;
    vector<string> _img_id_;
    vector<string> _font_id_;
    vector<string> _sound_id_;
    vector<string> _music_id_;

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
}*/

///
/// game_object


///
/// hud_object

void hud_object::update_pos()
{
    x=var::x;//+off_x;
    y=var::y;//+off_y;
}

///
/// hud_text

hud_text::hud_text(float off_xx,float off_yy,float zz,string stext,float fnum,unsigned int fontn)
{
    init();

    off_x=off_xx;
    off_y=off_yy;
    z=zz;

    text=stext;
    num=fnum;

    ltext=stext;
    lnum=fnum;

    sprite=drip_render_text(drip_get_font(0),text+number_to_string(num),0,200,50,255);

    visible=1;
    solid=0;
    remove=0;
    center=0;

    rect.w=sprite->w;
    rect.h=sprite->h;
    rect.x=x;
    rect.y=y;
}

void hud_text::update()
{
    //update_pos();
    x=var::x+off_x;
    y=var::y+off_y;

    if ( ltext==text && lnum==num);
    else
        sprite=drip_render_text(drip_get_font(0),text+number_to_string(num),0,200,50,255);

    rect.x=x;
    rect.y=y;

    string ltext=text;
    lnum=num;
}

void hud_text::set_text(string text_)
{
    text=text_;
}

void hud_text::set_num(float num_)
{
    num=num_;
}

void hud_text::call(string function,float num,string str)
{
    if (function=="set_text")
    {
        set_text(str);
    }

    if (function=="set_num")
    {
        set_num(num);
    }
}

///
/// tile


tile::tile(float xx,float yy,float zz,unsigned int image_num)
{
    init();

    move_mode=0;//(Xvol,Yvol,Zvol,speed) not (angle,speed)
    angle=0;
    speed=0;
    x=xx;
    y=yy;
    z=zz;

    sprite=drip_get_image(image_num);

    visible=1;
    solid=0;
    remove=0;
    center=0;

    type[0]="tile";
    type[1]="non-solid";
    type[2]="none";

    rect.w=sprite->w;
    rect.h=sprite->h;
    rect.x=x;
    rect.y=y;
}

///
/// brick


brick::brick(float xx,float yy,float zz,unsigned int image_num,int typen)
{
    init();

    move_mode=0;//(Xvol,Yvol,Zvol,speed) not (angle,speed)
    angle=0;
    speed=0;
    x=xx;
    y=yy;
    z=zz;

    sprite=drip_get_image(image_num);

    visible=1;
    solid=1;
    remove=0;
    center=0;

    type[0]="brick";
    type[1]="solid";
    type[2]="none";

    rect.w=sprite->w;
    rect.h=sprite->h;
    rect.x=x;
    rect.y=y;
}

void brick::update()
{
    update_rect();
}

///
/// ball

ball::ball(float xx,float yy,float zz,int typen)
{
    x=xx;
    y=yy;
    z=zz;

    init();

    move_mode=1;
    angle=0;
    speed=2;

    yvol=.1*((float) drip_random(-40,-30));
    xvol=.1*((float) drip_random(-60,60));


    sprite=drip_get_image(14);

    visible=1;
    solid=0;
    remove=0;
    center=0;

    type[0]="";
    type[1]="";
    type[2]="";
    rect.w=sprite->w;
    rect.h=sprite->h;
    rect.x=x;
    rect.y=y;
}

void ball::update()
{
    move();
    update_rect();


    if (x < 5)
    {
        xvol=-xvol;
        move();
    }

    if (x > var::map_width-21)
    {
        xvol=-xvol;
        move();
    }

    if (y < 5)
    {
        yvol=-yvol;
        move();
    }

    if (y > var::map_height-21)
    {
        yvol=.1*((float) drip_random(-40,-30));
        xvol=.1*((float) drip_random(-60,60));

        x=start_x;
        y=start_y;

        var::lives-=1;
    }

    int j=drip_rect_collide_all(rect,self);

    if (j)
    {
        bool f=0;
        game_object * g=resource::object.at(j-1);

        if (g->type[0]=="brick")
        {
            drip_play_sound(0);
            g->visible=0;
            g->solid=0;
            g->remove=1;
            if (yvol > 0)
                xvol=-xvol*((float) drip_random(5,20)*.1);
            yvol=-yvol*((float) drip_random(5,20)*.1);
            f=1;
        }

        if (g->type[0]=="player")
        {
            drip_play_sound(1);
            if (yvol < 0)
                xvol=-xvol*1.2;

            yvol=-yvol*((float) drip_random(5,20)*.1);

            move();
            f=1;
        }

        if (!f)
            cout << "Unknown Collision\n";
    }

    if (xvol < .5 && xvol >= 0)
        xvol=.5;
    if (xvol > -.5 && xvol <= 0)
        xvol=-.5;
    if (yvol < 2 && yvol > 0)
        yvol=2;
    if (yvol > -2 && yvol < 0)
        yvol=-2;

    if (xvol > 6 && xvol > 0)
        xvol=6;
    if (xvol < -6 && xvol < 0)
        xvol=-6;
    if (yvol > 6 && yvol > 0)
        yvol=6;
    if (yvol < -6 && yvol < 0)
        yvol=-6;
}

///
/// player

player::player(float xx,float yy,float zz)
{
    init();
    self=resource::object.size()-1;

    move_mode=1;//(Xvol,Yvol,Zvol,speed) not (angle,speed)
    angle=0;
    speed=3;
    x=xx;
    y=yy;
    z=zz;

    sprite=drip_get_image(0);

    visible=1;
    solid=1;
    remove=0;
    center=0;

    type[0]="player";
    type[1]="player-group";
    type[2]="player";

    rect.w=sprite->w;
    rect.h=sprite->h;
    rect.x=x;
    rect.y=y;

    var::lives=3;
}

void player::events()
{
    if (!var::joystick_enable)
    {
        Uint8 *keystate = SDL_GetKeyState(NULL);

        if ( keystate[SDLK_LEFT] )
            xvol=-speed;
        else
            if (xvol < 0)
                xvol=0;

        if ( keystate[SDLK_RIGHT] )
            xvol=speed;
        else
            if (xvol > 0)
                xvol=0;
    }
    else
    {
        xvol=((float) SDL_JoystickGetAxis(var::joystick, 0)/32767)*speed;
    }
}

void player::update()
{
    events();
    move();
    update_rect();

    //if (x-var::width/2 > 0)
    //    var::x=(x-var::width/2);

    //if (0 < y-var::height/2)
    //    var::y=(y-var::height/2);


    if (0 > x) x=0;
    if (0 > y) y=0;

    if (var::map_width-rect.w  < x) x=var::map_width-rect.w;
    if (var::map_height-rect.h  < y) y=var::map_height-rect.h;

}


