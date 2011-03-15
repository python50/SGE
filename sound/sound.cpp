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
 ** Sound.cpp
 **
 ** This file contains all of the standard sound code eg. play()
 **
 **/

#include "engine/engine.h"

// Music

void drip_play_music(unsigned int pos,int loopn)// 1- = forever 0=1 1=2 etc
{
    if(Mix_PlayMusic(resource::music.at(pos), loopn)==-1)
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
}

void drip_stop_music()
{
    Mix_HaltMusic();
}

void drip_pause_music()
{
    Mix_PauseMusic();
}

void drip_unpause_music()
{
    Mix_ResumeMusic();
}

void drip_music_position(double pos)
{
    Mix_RewindMusic();
    if(Mix_SetMusicPosition(pos)==-1)
        printf("Mix_SetMusicPosition: %s\n", Mix_GetError());
}

// Sound

void drip_play_sound(unsigned int pos)
{
    if(Mix_PlayChannel(-1, resource::sound.at(pos), 0)==-1)
        printf("Mix_PlayChannel: %s\n",Mix_GetError());
}

void drip_stop_sound()
{
    Mix_HaltChannel(-1);
}

void drip_pause_sound()
{
    Mix_Pause(-1);
}

void drip_unpause_sound()
{
    Mix_Resume(-1);
}

void drip_fadeout_sound(float seconds)
{
    Mix_FadeOutChannel(-1, seconds/1000);
}
