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
 ** String.cpp
 **
 ** This file contains some random string code
 **
 **/

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

int drip_file_write(string filename,string data,long pos)
{
    const char * filen = filename.c_str();

    cout << "Event: file written " << filename << "\n";

    ofstream file;
    file.open(filen);
    file.seekp(pos);
    file << data << endl;
    file.close();

    return 0;
}

string drip_file_load(string filename)//standard text
{
    const char * filen = filename.c_str();
    string line;
    string data;
    ifstream file (filen);

    if (file.is_open())
    {
        cout << "Event: file opened " << filename << "\n";

        while (! file.eof() )
        {
            getline (file,line);
            data+=line;
        }
            file.close();
            return data;
    }

    cout << "Error: failed to open " << filen << "\n";

    return "";

}

string drip_string_copy(string str,int pos1,int pos2)
{
    str.erase(0,pos1);
    str.erase((pos2)-(pos1));
    return str;
}

std::string number_to_string(int num)
{
    std::stringstream out;
    out << num;
    return out.str();
}

int string_to_number(std::string str)
{
  int intReturn;

  intReturn = atoi(str.c_str());

  return(intReturn);
}
