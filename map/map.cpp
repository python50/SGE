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
 ** Map.cpp
 **
 ** This file contains all of the map functions ! NEEDS DEBUGING!!!
 **
 **/

#include "engine/engine.h"
#include <stdio.h>
#include <cstdlib>
#include <fstream>

void drip_map_data_process(string cmdclass,string params)
{
    if (cmdclass=="$,")
    {
        if (params.find("name,") < params.size())
        {
            var::map_name=drip_string_copy(params,5,params.find(";"));
        }

        if (params.find("author,") < params.size())
        {
            var::map_author=drip_string_copy(params,7,params.find(";"));
        }

        if (params.find("description,") < params.size())
        {
            var::map_description=drip_string_copy(params,12,params.find(";"));
        }

        if (params.find("difficulty,") < params.size())
        {
            var::map_difficulty=drip_string_copy(params,11,params.find(";"));
        }

        if (params.find("date,") < params.size())
        {
            var::map_date=drip_string_copy(params,5,params.find(";"));
        }

        if (params.find("size,") < params.size())
        {
            int w=atoi(drip_string_copy(params,5,5+5).c_str());
            int h=atoi(drip_string_copy(params,11,11+5).c_str());
            var::map_width=w;
            var::map_height=h;
        }
    }

    if (cmdclass=="3,")
    {
        if (params.find("player,") < params.size())
        {
            int x=atoi(drip_string_copy(params,7,7+5).c_str());
            int y=atoi(drip_string_copy(params,7+6,7+11).c_str());
            int z=atoi(drip_string_copy(params,7+12,7+17).c_str());
            resource::object.push_back(new player(x,y,z));
        }
    }

    if (cmdclass=="4,")
    {
        if (params.find("tile,") < params.size())
        {
            int x=atoi(drip_string_copy(params,5,5+5).c_str());
            int y=atoi(drip_string_copy(params,11,11+5).c_str());
            int z=atoi(drip_string_copy(params,17,17+5).c_str());
            int i=atoi(drip_string_copy(params,23,23+5).c_str());
            resource::object.push_back(new tile(x,y,z,i));
        }

        if (params.find("ball,") < params.size())
        {
            int x=atoi(drip_string_copy(params,5,5+5).c_str());
            int y=atoi(drip_string_copy(params,11,11+5).c_str());
            int z=atoi(drip_string_copy(params,17,17+5).c_str());
            int t=atoi(drip_string_copy(params,23,23+5).c_str());
            resource::object.push_back(new ball(x,y,z,t));
        }
    }

    if (cmdclass=="5,")
    {
        if (params.find("brick,") < params.size())
        {
            int x=atoi(drip_string_copy(params,6,6+5).c_str());
            int y=atoi(drip_string_copy(params,12,12+5).c_str());
            int z=atoi(drip_string_copy(params,18,18+5).c_str());
            int i=atoi(drip_string_copy(params,24,24+5).c_str());
            int t=atoi(drip_string_copy(params,30,30+5).c_str());
            resource::object.push_back(new brick(x,y,z,i,t));
        }
    }
}

void drip_map_load(string file)
{
    file=var::data_dir+"maps/"+file;

    string data=drip_file_load(file);

    unsigned int pos=0;
    unsigned int old_pos=0;
    while(1)
    {
        bool found=0;

        if (pos>=data.size())
        {
            break;
        }

        if (drip_string_copy(data,pos,pos+2)=="/*")
        {
            found=1;
            pos=data.find("*/",pos)+2;
            continue;
        }

        if (drip_string_copy(data,pos,pos+2)=="$,")
        {
            found=1;
            old_pos=pos;
            pos=data.find(";",pos)+1;
            drip_map_data_process(drip_string_copy(data,old_pos,old_pos+2),drip_string_copy(data,old_pos+2,pos));
            continue;
        }

        if (drip_string_copy(data,pos,pos+2)=="3,")
        {
            found=1;
            old_pos=pos;
            pos=data.find(";",pos)+1;
            drip_map_data_process(drip_string_copy(data,old_pos,old_pos+2),drip_string_copy(data,old_pos+2,pos));
            continue;
        }

        if (drip_string_copy(data,pos,pos+2)=="4,")
        {
            found=1;
            old_pos=pos;
            pos=data.find(";",pos)+1;
            drip_map_data_process(drip_string_copy(data,old_pos,old_pos+2),drip_string_copy(data,old_pos+2,pos));
            continue;
        }

        if (drip_string_copy(data,pos,pos+2)=="5,")
        {
            found=1;
            old_pos=pos;
            pos=data.find(";",pos)+1;
            drip_map_data_process(drip_string_copy(data,old_pos,old_pos+2),drip_string_copy(data,old_pos+2,pos));
            continue;
        }

        if (!found)
        {
            bool break_loop=1;

            cout << "error loading map !\n" << "Position: " << pos << "\n";
            cout << "Last Valid Command: " << drip_string_copy(data,old_pos,pos) << "\n";

            if (!data.find(";",pos+1)==data.npos)
            {
                string bad_cmd=drip_string_copy(data,pos,data.find(";",pos)+1);
                cout << "Invalid Command: " << bad_cmd << "\n";
                break_loop=0;
                pos=data.find(";",pos);
            }
            else
            {
                cout << "Invalid Command: No ; terminated command ?\n";
                cout << "Dumping To End:\n" << drip_string_copy(data,pos,data.size()-1) << "\n";
            }
            if (break_loop)
            {
                cout << "No further commands found, quiting loading loop\n";
                break;
            }
            else
            {
                cout << "Further commands found, continuing loading loop\n";
                continue;
            }
        }
    }

    cout << "Event: Map Loaded "+file+"\n";
    cout << "\tMap Name: " << var::map_name << "\n";
    cout << "\tAuthor: "<< var::map_author << "\n";
    cout << "\tDescription: "<< var::map_description << "\n";
    cout << "\tDifficulty: "<< var::map_difficulty << "\n";
    cout << "\tDate: "<< var::map_date<< "\n";


}

void load_resource_list()
{
    string data=drip_file_load("./data/resources.conf");

    if (data.size()==0)
        cout << "error \n";

    unsigned int pos=0;
    unsigned int old_pos=0;
    while(1)
    {
        bool found=0;

        if (pos>=data.size())
        {
            break;
        }

        if (drip_string_copy(data,pos,pos+2)=="/*")
        {
            found=1;
            pos=data.find("*/",pos)+2;
            continue;
        }

        if (drip_string_copy(data,pos,data.find(",",pos))=="test")
        {
            found=1;
            cout << "FOUND IT !" << "\n";
            old_pos=pos;
            pos=data.find(";",pos)+1;
            continue;
        }

        if (!found)
        {
            bool break_loop=1;

            cout << "error loading map !\n" << "Position: " << pos << "\n";
            cout << "Last Valid Command: " << drip_string_copy(data,old_pos,pos) << "\n";

            if (!data.find(";",pos+1)==data.npos)
            {
                string bad_cmd=drip_string_copy(data,pos,data.find(";",pos)+1);
                cout << "Invalid Command: " << bad_cmd << "\n";
                break_loop=0;
                pos=data.find(";",pos);
            }
            else
            {
                cout << "Invalid Command: No ; terminated command ?\n";
                cout << "Dumping To End:\n" << drip_string_copy(data,pos,data.size()-1) << "\n";
            }
            if (break_loop)
            {
                cout << "No further commands found, quiting loading loop\n";
                break;
            }
            else
            {
                cout << "Further commands found, continuing loading loop\n";
                continue;
            }
        }
    }

}

