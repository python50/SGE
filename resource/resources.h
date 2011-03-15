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
 ** Resouces.h
 **
 ** This file contains all of the declarations for resource loading / geting
 **
 **/

#include "engine/engine.h"

#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

// Load

unsigned int drip_load_font(string file, string id, int ptsize);

unsigned int drip_load_image(string file, string id, int colorkey);

unsigned drip_load_music(string file, string id);

unsigned drip_load_sound(string file, string id);

// Get

SDL_Surface * drip_get_image(unsigned int img_num);
SDL_Surface * drip_get_image(string id);

Mix_Music * drip_get_music(unsigned int mus_num);
Mix_Music * drip_get_music(string id);

Mix_Chunk * drip_get_sound(unsigned int snd_num);
Mix_Chunk * drip_get_sound(string id);

TTF_Font * drip_get_font(unsigned int font_num);
TTF_Font * drip_get_font(string id);

unsigned int drip_get_object(string type,int typen);

// set

SDL_Surface * drip_set_colorkey(SDL_Surface * image);


#endif // RESOURCES_H_INCLUDED
