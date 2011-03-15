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
 ** Engine.h
 **
 ** This is he meta header file containing all on the other headers
 **
 **/

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include "sdl_gfx/SDL_framerate.h"
//#include "sdl_gfx/SDL_gfxBlitFunc.h"
//#include "sdl_gfx/SDL_gfxPrimitives.h"
//#include "sdl_gfx/SDL_gfxPrimitives_font.h"
//#include "sdl_gfx/SDL_imageFilter.h"
#include "sdl_gfx/SDL_rotozoom.h"

#include <iostream>

#include "collision/collision.h"
#include "error/error.h"
#include "engine/engine_data.h"
#include "map/map.h"
#include "object/objects.h"
#include "math/random.h"
#include "render/render.h"
#include "resource/resources.h"
#include "sound/sound.h"
#include "string/string.h"
#include "math/tdmath.h"
#include "settings.h"

using namespace std;


/// System

// Start the system

SDL_Surface * init(char caption[255],int width , int height , bool fullscreen , bool cursor , int soundvolume , int musicvolume);

// load up all the system resources

bool load();

// update objects

void update(SDL_Surface * screen);

// quit game and free resources

void quit();

//

void regulate_fps(int fps=30);

#endif // ENGINE_H_INCLUDED
