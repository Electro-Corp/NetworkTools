/*
    NetworkTools - Network Analysis Tool
    arguments.hpp - header for argument parsing

    Copyright (C) 2026 Electro-Corp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once

#include <string>
#include <cstring>
#include <iostream>

// Get variable in command line
static std::string getParam(char* command, int args, char* argv[]){
    for(int i = 0; i < args; i++){
        if(strcmp(command, argv[i]) == 0){
            if(i + 1 < args){
                return std::string{argv[i + 1]};
            }else{
                std::cout << "ERROR: " << argv[i] << " requires a parameter!\n";
                exit(-1);
            }
        }
    }
    return "";
}

// Does param exist
static int doesParamExist(char* command, int args, char* argv[]){
    for(int i = 0; i < args; i++){
        if(strcmp(command, argv[i]) == 0){
            return 1;
        }
    }
    return 0;
}