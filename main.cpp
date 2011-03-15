/*
 * Copyright (c) 2010, Jason White <whitewaterssoftwareinfo@gmail.com>
 *                           wwsoft.co.cc / wwsoft.dyndns.info
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

/**unsigned int
 ** Main.cpp
 **
 ** This is the main loop
 **
 **/


#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include <cstdio>
#include <iostream>
#include <time.h>
#include <cmath>
#include "engine/engine.h"
#include "string/string.h"


SDL_Surface * screen; // its the screen !

void event();

void error_handle();

int main ( int argc, char** argv )
{
    // Window Title, Width, Height, Fullscreen, Cursor, Sound Volume, Music Volume
    screen=init("Teroids",640,480,0,0,128,128);

    if (!screen)
    {
        cout << endl << "Fatal Error: Unable To Initialize" << endl;
        return 0;
    }

    if (!load())
    {
        cout << endl << "Fatal Error: Unable To Load Resources" << endl;
        return 0;
    }

    drip_play_sound(2);

    //drip_play_music(1,0);
    //string gconfig=drip_file_load("./data/maps/test.wmap");
    drip_map_load("menu.wmap");

    while (var::quit==0)
    {
        regulate_fps(30);
        //error_handle();
        event();
        SDL_FillRect(::screen, 0, SDL_MapRGB(screen->format, 0x00, 0x00 , 0x88));
        update(screen);

        if (var::fps_enable)
        {
            drip_blit(4,2,drip_render_text(drip_get_font(0),"FPS: "+convertintstr(var::display_fps),0xFF,0x88,0),screen,1);
            drip_blit(4,14,drip_render_text(drip_get_font(0),"Joystick: "+convertintstr(var::joystick_enable),0xFF,0x88,0),screen,1);
        }

        drip_blit(5,3,drip_render_text(drip_get_font(1),"Lives: "+convertintstr(var::lives),0x00,0x00,0x00),screen,1);
        drip_blit(4,2,drip_render_text(drip_get_font(1),"Lives: "+convertintstr(var::lives),0xFF,0xFF,0xFF),screen,1);

        SDL_Flip(screen);
    }

    quit();

    printf("Player Quit\n");
    return 0;
}

void event()
{
    while (SDL_PollEvent(&var::event))
    {
        switch (var::event.type)
        {
            case SDL_QUIT:
            {
                var::quit = true;
                break;
            }

            case SDL_KEYDOWN:
            {
                if (var::event.key.keysym.sym == SDLK_ESCAPE)
                {
                    var::quit = true;
                    break;
                }

                if (var::event.key.keysym.sym == SDLK_q)
                {
                    var::quit = true;
                    break;
                }

                if (var::event.key.keysym.sym == SDLK_j)
                {
                    if (var::joystick_enable)
                        var::joystick_enable=0;
                    else
                        var::joystick_enable=1;

                    drip_play_sound(2);
                    break;
                }

                if (var::event.key.keysym.sym == SDLK_f)
                {
                    if (var::fps_enable)
                        var::fps_enable=0;
                    else
                        var::fps_enable=1;

                    drip_play_sound(2);
                    break;
                }


                if (var::event.key.keysym.sym == SDLK_PRINT)
                {
                    time_t rawtime;
                    time ( &rawtime );
                    string stimes="./data/screenshots/screen"+convertintstr(rawtime)+" "+convertintstr(drip_random(0,99999))+".bmp";
                    SDL_SaveBMP(screen, stimes.c_str());
                    cout << "Screenshot: " << stimes << " added\n";
                }

                if (var::event.key.keysym.sym == SDLK_PAUSE)
                {
                    if (var::pause)
                        var::pause=0;
                    else
                        var::pause=1;

                    break;
                }

            }
        }
    }
}


