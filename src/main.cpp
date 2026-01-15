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
#include <cstring>

// Network tool
#include "network.hpp"
// Include all modules
#include "module.hpp" // base
#include "modules/module_dump.hpp" // dump network traffic

//
// Variables for main
// 

// Moudles
std::vector<NetworkTools::Module> modules;
// Network engine
NetworkTools::NetworkEngine networkEngine;
// Variables
std::string card;

//
// Functions for main
//

// Parse args
int parseArguments(int args, char* argv[]);
// Get variable in command line
std::string getParam(char* command, int args, char* argv[]);
// Print help
void printHelp();

int main(int args, char* argv[]){
    // List all devices
    networkEngine.printDeviceNames();
    // Create Program list
    modules.push_back(Modules::Dump());

    if(parseArguments(args, argv) != 0){
        printHelp();
        exit(-1);
    }

    // Select card
    if(card.empty()){
        networkEngine.selectDefaultDevice();
    }else{
        if(!networkEngine.selectDevice(card)){
            std::cout << "ERROR: Device: " << card << " not found!\n";
            exit(-1);
        }
    }

    std::cout << "Using device: " << networkEngine.getSelectedDevice()->name << "\n";

    return 0;
}

// Parse args
int parseArguments(int args, char* argv[]){
    if(args < 3){
        std::cout << "ERROR: No module selected!\n";
        return -1;
    }

    card = getParam("-device", args, argv);

    return 0;
}

// Get variable in command line
std::string getParam(char* command, int args, char* argv[]){
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

// Print help
void printHelp(){
    std::cout << "================================================\n";
    std::cout << "NetworkTools - Copyright (C) 2026 Electro-Corp\n";
    std::cout << "Usage: ./networkTools [module] [optional]\n";
    std::cout << "================================================\n";
    std::cout << "Modules: \n";
    for(auto& mod : modules) std::cout << "> " << mod.getModuleName() << "\n";
    std::cout << "================================================\n";
    std::cout << "Options: \n";
    std::cout << "-device [deviceName]  Select Specfic Device\n";
    std::cout << "================================================\n";
}