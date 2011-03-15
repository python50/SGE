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
 ** Engine.cpp
 **
 **   This file contains the code to start/kill the engine
 **
 **/


#define VERSION "1.0a  3/29/2010 (M-D-Y)"

/*#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>*/

#include <algorithm>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "engine/engine.h"


using namespace std;

// Start the system

SDL_Surface * init(char caption[255],int width , int height , bool full , bool cursor , int soundvolume , int musicvolume)
{
    string debug_lev="";
    if (DEBUG_LEVEL==0)
        debug_lev="(Errors Only)";
    if (DEBUG_LEVEL==1)
        debug_lev="(Warnings, Errors)";
    if (DEBUG_LEVEL==2)
        debug_lev="(Warnings, Errors , Events)";

    cout << "Compiled Settings\n" << "-----------------\n\n";
    cout << "\tDEBUG LEVEL: " << DEBUG_LEVEL << " "+debug_lev << endl;
    cout << "\tGENERATE EMPTY: " << GENERATE_EMPTY << endl;
    cout << "\n";

    var::width=width;
    var::height=height;

    atexit(SDL_Quit);
    drip_randomize();

    var::data_dir="./data/"; // for cross system installs

    if ( SDL_Init( SDL_INIT_EVERYTHING) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 0;
    }

    // screen
    SDL_Surface * screen;
    if (full)
        screen = SDL_SetVideoMode(width, height, 32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode(width, height, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    var::format=screen->format;

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 180));

    if ( !(screen) )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 0;
    }

    // subsystems

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2,  1024)==-1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return 0;
    }
    else
    {
        Mix_AllocateChannels(64);
        Mix_Volume(1,soundvolume);
        Mix_VolumeMusic(musicvolume);
    }

    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        return 0;
    }

    // Check for joystick
    if(SDL_NumJoysticks()>0)
    {
        // Open joystick
        var::joystick=SDL_JoystickOpen(0);

        if(var::joystick)
        {
            printf("Opened Joystick 0\n");
            printf("Name: %s\n", SDL_JoystickName(0));
            printf("Number of Axes: %d\n", SDL_JoystickNumAxes(var::joystick));
            printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(var::joystick));
            printf("Number of Balls: %d\n", SDL_JoystickNumBalls(var::joystick));
        }
        else
            printf("Couldn't open Joystick 0\n");
    }
    else
        printf("No Joysticks Available\n");

    SDL_WM_SetCaption(caption,0);

    if (cursor)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);

    cout << "Initialized" << endl;

    return screen;
}

// load up all the system resources

bool load()
{
    /// /// load music

    drip_load_music("starcade-chandelier.ogg","chandelier");//0
    drip_load_music("amiga_style.mod","amiga_style"); //1

    /// /// load sounds

    drip_load_sound("break.wav","break"); //0
    drip_load_sound("impact.wav","impact"); //1
    drip_load_sound("beep0.wav","beep0"); //2

    /// /// load fonts

    drip_load_font("FreeSans.ttf","freesans12",12); //0
    drip_load_font("FreeSans.ttf","freesans24",24); //1

    /// /// load surfaces

    drip_load_image("paddle0.png","paddle0",0); //0
    drip_load_image("brick0.png","brick0",0); //1
    drip_load_image("brick1.png","brick1",0); //2
    drip_load_image("brick2.png","brick2",0); //3
    drip_load_image("brick3.png","brick3",0); //4
    drip_load_image("brick4.png","brick4",0); //5
    drip_load_image("brick5.png","brick5",0); //6
    drip_load_image("brick6.png","brick6",0); //7
    drip_load_image("brick7.png","brick7",0); //8
    drip_load_image("brick8.png","brick8",0); //9
    drip_load_image("brick9.png","brick9",0); //10
    drip_load_image("brick10.png","brick10",0); //11
    drip_load_image("brick11.png","brick11",0); //12
    drip_load_image("bubbles.png","bubbles_bg",0); //13
    drip_load_image("ball0.png","ball0",0); //14
    drip_load_image("menu.png","menu_text",0); //15

    void load_resource_list();

    cout << "Loaded" << endl; // all loaded up !

    return 1;
}


template<typename Object>

struct PointerComp
{
    bool operator()(const Object* lhs, const Object* rhs)const
    {
        return lhs->z < rhs->z;
    }
};


// update objects

void update(SDL_Surface * screen)
{
    if (var::sort_z)
    {
        std::sort(resource::object.begin(),resource::object.end(),PointerComp<game_object>());
        var::sort_z=0;
    }

    unsigned int lenth=resource::object.size();
    for (unsigned int i=0; i < lenth; i+=1)
    {
        SDL_Rect A; //screen collision bounding box

        A.x=var::x;
        A.y=var::y;
        A.h=var::height;
        A.w=var::width;

        SDL_Rect B; //object collision bounding box

        B=resource::object.at(i)-> get_rect();

        B.x=round(B.x+var::x);
        B.y=round(B.y+var::y);
        B.w=resource::object.at(i)->sprite->w;
        B.h=resource::object.at(i)->sprite->h;

        if (drip_rect_collide(A,B) && ! var::pause)
        {
            game_object * obj = resource::object.at(i);
            obj -> update();

            if (obj->visible)
            {
                if (obj-> center)
                    drip_blit( obj -> x-(obj->sprite->w/2)-var::x , obj -> y-(obj->sprite->h/2)-var::y, obj -> sprite ,screen);
                else
                    drip_blit( obj -> x-var::x , obj -> y-var::y, obj -> sprite ,screen);
            }
        }

    }
}

// quit game and free resources

void quit()
{
//    Mix_Quit();
    TTF_Quit();
//    IMG_Quit();

    unsigned int size=0;

    try
    {
        size=resource::object.size()-1;
        if (size < 0)
        {
            for (unsigned int i=0; i < size; i+=1)
            {
                delete &resource::object.at(i);
            }
        }
    }
    catch(...)
    {
        cout << "Free Failure: 1" << endl;
    }

    try
    {
        size=resource::music.size()-1;
        if (size < 0)
        {
            for (unsigned int i=0; i < size; i+=1)
                Mix_FreeMusic(resource::music.at(i));
        }
    }
    catch(...)
    {
        cout << "Free Failure: 2" << endl;
    }

    try
    {
        size=resource::sound.size()-1;
        if (size < 0)
        {
            for (unsigned int i=0; i < size; i+=1)
                Mix_FreeChunk(resource::sound.at(i));
        }
    }
    catch(...)
    {
        cout << "Free Failure: 3" << endl;
    }

    try
    {
        size=resource::font.size()-1;
        if (size < 0)
        {
            for (unsigned int i=0; i < size; i+=1)
                TTF_CloseFont(resource::font.at(i));
        }
    }
    catch(...)
    {
        cout << "Free Failure: 4" << endl;
    }

    try
    {
        size=resource::image.size()-1;
        if (size < 0)
        {
            for (unsigned int i=0; i < size; i+=1)
                SDL_FreeSurface(resource::image.at(i));
        }
    }
    catch(...)
    {
        cout << "Free Failure: 5" << endl;
    }

    if(SDL_JoystickOpened(0))
        SDL_JoystickClose(var::joystick);

    cout << "Freed Resources" << endl;
}

void regulate_fps(int fps)
{

    var::last_ticks=var::current_ticks;
    var::current_ticks=SDL_GetTicks();

    if ((var::last_ticks) && (var::current_ticks ))
        var::current_fps=round(1000/((var::current_ticks)-(var::last_ticks)));

    if (var::last_update < var::current_ticks-50 )
    {
        var::display_fps=round(((var::current_fps)+var::display_fps)/2);
        var::last_update=var::current_ticks;
    }

    int ticks=round((var::current_ticks)-(var::last_ticks));
    int ticks_goal=1000/fps;

    var::tick_delay=(ticks_goal-ticks)+5;
    if (var::tick_delay < 0)
        var::tick_delay=0;

    SDL_Delay(var::tick_delay);
}
