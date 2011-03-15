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
 ** Collisions.cpp
 **
 ** This file contains all of the standard collision code
 **
 **/

#include "engine/engine.h"

int drip_rect_collide(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;	//just checking if their
	if(b.x > a.x + a.w)	return 0;	//bounding boxes even touch

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	return 1;				//bounding boxes intersect
}


unsigned int drip_rect_collide_all(SDL_Rect rect,unsigned self)
{
    unsigned int size = resource::object.size();
    for(unsigned int i=0;i < size;i+=1)
    {
        if ( resource::object.at(i)->solid==1 )
        {
            if ( drip_rect_collide(rect,resource::object.at(i)->rect ) )
            {
                if (i==self)
                {
                    return 0;
                }
                else
                {
                    return i+1;
                }
            }
        }

    }

    return 0;
}

int drip_get_distance(int x1,int y1,int x2,int y2)
{
    return sqrt( ((x2 - x1)^2) + ((y2 - y1)^2) );
}

unsigned int drip_rect_collide_circle(int radius,int x1 ,int y1,unsigned self)
{
    unsigned int size = resource::object.size();
    for(unsigned int i=0;i < size;i+=1)
    {
        if ( resource::object.at(i)->solid==1 )
        {
            game_object * o=resource::object.at(i);
            cout << drip_get_distance(x1,y1,o->x,o->y) << "\n";
            if ( drip_get_distance(x1,y1,o->x,o->y) <= radius || -drip_get_distance(x1,y1,o->x,o->y) <= radius)
            {
                if (!i==self)
                {
                    cout << "C\n";
                    return i+1;
                }
            }
        }

    }

    return 0;
}
