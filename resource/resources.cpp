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
 ** Resouces.cpp
 **
 ** This file contains all of the standard resource loading / geting code
 **
 **/

#include "engine/engine.h"
#include "render/render.h"

// Load

unsigned int drip_load_font(string file, string id, int ptsize)
{
    try
    {
        file=var::data_dir+"fonts/"+file;
        char * cstr = new char [file.size()+1];
        strcpy (cstr, file.c_str());

        TTF_Font *font;
        font=TTF_OpenFont(cstr, ptsize);

        if(!font)
        {
            delete[] cstr;
            throw (string) TTF_GetError();
        }

        resource::font.push_back(font);
        resource::font_id.push_back(id);
        if (DEBUG_LEVEL > 1)
            cout <<  "Event: Font Loaded, " << file << " ID " << id << " Added, Index " << resource::font.size()-1 << "\n";
        delete[] cstr;
        return resource::object.size()-1;
    }
    catch(string str)
    {
        cout << "ERROR [FONT LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }

    return 0;
}

unsigned int drip_load_image(string file, string id, int colorkey)
{
    try
    {
        file=var::data_dir+"images/"+file;
        char * cstr = new char [file.size()+1];
        strcpy (cstr, file.c_str());

        SDL_Surface *image;
        image=IMG_Load(cstr);

        if(!image)
        {
            delete[] cstr;
            throw IMG_GetError();
        }

        if (colorkey==1)
        {
            long colorkey = SDL_MapRGB(var::format, 255, 0, 255);
            SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
        }

        if (colorkey==1)
            resource::image.push_back(SDL_DisplayFormat(image));
        else
            resource::image.push_back(image);

        resource::image_id.push_back(id);

        if (DEBUG_LEVEL > 1)
            cout <<  "Event: Image Loaded, " <<file << " ID " << id << " Added, Index " << resource::image.size()-1 << "\n";

        delete[] cstr;
        return resource::image.size()+1;
    }
    catch(string str)
    {
        cout << "ERROR [IMAGE LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }
    return 0;
}

unsigned drip_load_music(string file, string id)
{
    try
    {
        file=var::data_dir+"music/"+file;
        char * cstr = new char [file.size()+1];
        strcpy (cstr, file.c_str());

        Mix_Music *music;
        music=Mix_LoadMUS(cstr);
        if(!music)
        {
            delete[] cstr;
            throw Mix_GetError();
        }

        resource::music.push_back(music);
        resource::music_id.push_back(id);
        if (DEBUG_LEVEL > 1)
            cout <<  "Event: Music Loaded, " <<file << " ID " << id << " Added, Index " << resource::music.size()-1 << "\n";
        delete[] cstr;
        return resource::music.size()-1;
    }
    catch(string str)
    {
        cout << "ERROR [MUSIC LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;

    }

    return 0;
}

unsigned drip_load_sound(string file, string id)
{
    try
    {
        file=var::data_dir+"sound/"+file;
        char * cstr = new char [file.size()+1];
        strcpy (cstr, file.c_str());

        Mix_Chunk * sound;
        sound=Mix_LoadWAV(cstr);
        if(!sound)
        {
            delete[] cstr;
            throw Mix_GetError();
        }

        resource::sound.push_back(sound);
        resource::sound_id.push_back(id);

        if (DEBUG_LEVEL > 1)
            cout <<  "Event: Sound Loaded, " << file << " ID " << id << " Added, Index " << resource::sound.size()-1 << "\n";

        delete[] cstr;
        return resource::sound.size()+1;
    }
    catch(string str)
    {
        cout << "ERROR [SOUND LOAD]: " << str << endl;

        if (DEBUG_LEVEL > 0)
            cout << "WARNING: THIS CAN CAUSE A CRASH" << endl;
    }

    return 0;
}

// Get

SDL_Surface * drip_get_image(unsigned int img_num)
{
    try
    {
        if (! ((unsigned int)resource::image_id.size()-1) <= img_num) // is the vector as big as the resorce index provided
        {
            return resource::image.at(img_num);
        }
        else
            throw img_num;
    }
    catch(unsigned int n)
    {
        cout << "ERROR [IMAGE ACCESS]: IMAGE AT INDEX " << n << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATING EMPTY DATATYPE" << endl;

            return SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0xFFFFFFFF); //32x32, 32 bit black square
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
                cout << "Exiting ...\n";
            exit(0);
        }
    }
}

SDL_Surface * drip_get_image(string id)
{
    try
    {
        for(unsigned int i=0;i < resource::image_id.size()-1;i+=1)
        {
            if (resource::image_id.at(i)==id)
                return resource::image.at(i);
        }

        throw id; //error
    }
    catch(string id)
    {
        cout << "ERROR [IMAGE ACCESS]: IMAGE " << id << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATING EMPTY DATATYPE" << endl;

            return SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, 32, 0, 0, 0, 0xFFFFFFFF); //32x32, 32 bit black square
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
                cout << "Exiting ...\n";
            exit(0);
        }
    }
}

Mix_Music * drip_get_music(unsigned int mus_num)
{
    try
    {

        if (! ((unsigned int)resource::music_id.size()-1) <= mus_num) // is the vector as big as the resorce index provided
        {
            return resource::music.at(mus_num);
        }
        else
            throw mus_num;
    }
    catch(unsigned int n)
    {
        cout << "ERROR [MUSIC ACCESS]: SOUND AT INDEX " << n << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}


Mix_Music * drip_get_music(string id)
{
    try
    {
        for(unsigned int i=0;i < resource::music_id.size()-1;i+=1)
        {
            if (resource::music_id.at(i)==id)
                return resource::music.at(i);
        }

        throw id; //error
    }
    catch(string id)
    {
        cout << "ERROR [MUSIC ACCESS]: SOUND " << id << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}

Mix_Chunk * drip_get_sound(unsigned int snd_num)
{
    try
    {
        if (! ((unsigned int)resource::sound_id.size()-1) <= snd_num) // is the vector as big as the resorce index provided
        {
            return resource::sound.at(snd_num);
        }
        else
            throw snd_num;
    }
    catch(unsigned int n)
    {
        cout << "ERROR [SOUND ACCESS]: SOUND AT INDEX " << n << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0); // is the vector as big as the resorce index provided
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}

Mix_Chunk * drip_get_sound(string id)
{
    try
    {
        for(unsigned int i=0;i < resource::sound_id.size()-1;i+=1)
        {
            if (resource::sound_id.at(i)==id)
                return resource::sound.at(i);
        }

        throw id; //error
    }
    catch(string id)
    {
        cout << "ERROR [SOUND ACCESS]: SOUND " << id << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0); // is the vector as big as the resorce index provided
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}

TTF_Font * drip_get_font(unsigned int font_num)
{
    try
    {
        if (! ((unsigned int)resource::font_id.size()-1) <= font_num) // is the vector as big as the resorce index provided ?
        {
            return resource::font.at(font_num);
        }
        else
            throw font_num;
    }
    catch(unsigned int n)
    {
        cout << resource::font.size()-1 << endl;
        cout << "ERROR [FONT ACCESS]: FONT AT INDEX " << n << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}

TTF_Font * drip_get_font(string id)
{
    try
    {
        for(unsigned int i=0;i < resource::font_id.size()-1;i+=1)
        {
            if (resource::font_id.at(i)==id)
                return resource::font.at(i);
        }

        throw id; //error
    }
    catch(string id)
    {
        cout << resource::font.size()-1 << endl;
        cout << "ERROR [FONT ACCESS]: FONT " << id << " DOES NOT EXIST" << endl;
        if (GENERATE_EMPTY)
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: CANNOT GENERATE EMPTY DATATYPE" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
        else
        {
            if (DEBUG_LEVEL > 1)
                cout << "EVENT: GENERATE EMPTY DATATYPE IS OFF" << endl;
            cout << "Exiting ...\n";

            exit(0);
        }
    }
}

unsigned int drip_get_object(string type,int typen)
{
    for(unsigned int i=0;i < resource::object.size()-1;i+=1)
    {
        if (resource::object.at(i)->type[typen]==type)
            return i+1;
    }

    return 0;
}

SDL_Surface * drip_set_colorkey(SDL_Surface * image)
{
    long colorkey = SDL_MapRGB(var::format, 0, 0, 0);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    return image;
}
