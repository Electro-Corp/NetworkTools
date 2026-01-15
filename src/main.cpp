/*
    NetworkTools - Network Analysis Tool
    main.cpp - Entry point

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
#include <iostream>
#include <vector>

// Include all modules
#include "module.hpp" // base
#include "modules/module_dump.hpp" // dump network traffic

// Moudles
std::vector<NetworkTools::Module> modules;

// Parse args
int parseArguments(int args, char* argv[]);

// Print help
void printHelp();

int main(int args, char* argv[]){
    // Create Program list
    modules.push_back(Modules::Dump());

    if(parseArguments(args, argv) != 0){
        printHelp();
        exit(-1);
    }

    return 0;
}

// Parse args
int parseArguments(int args, char* argv[]){
    if(args < 2) return -1;

    // Go through each command
    for(int i = 1; i < args; i++){
        
    }

    return 0;
}


// Print help
void printHelp(){
    std::cout << "NetworkTools - Copyright (C) 2026 Electro-Corp\n";
    std::cout << "Usage: ./networkTools [module] [optional]\n";
    std::cout << "Modules: \n";
    for(auto& mod : modules) std::cout << "- " << mod.getModuleName() << "\n";
    std::cout << "Options: \n";
    std::cout << "-card     Select Specfic Network Card\n";
}