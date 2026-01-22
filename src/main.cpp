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
#include <csignal>

// Network tool
#include "network.hpp"
// Argument parser
#include "arguments.hpp"
// Include all modules
#include "modules/module_dump.hpp" // dump network traffic
#include "modules/module_urlgrab.hpp" // get urls from packets
#include "modules/module_repeat.hpp" // find repeated data

//
// Variables for main
// 

// Moudles
std::vector<NetworkTools::Module*> modules;
// Network engine
NetworkTools::NetworkEngine networkEngine;
// Variables
std::string card;

//
// Functions for main
//

// Parse args
NetworkTools::Module* parseArguments(int args, char* argv[]);
// Print help
void printHelp();
// Print warning
void printWarning();
// Signals
void setupSignals();
void segfaultSignal(int);
void interruptSignal(int);
// Clean up
void cleanup();

int main(int args, char* argv[]){
    setupSignals();
    // List all devices
    networkEngine.printDeviceNames();
    // Create Program list
    modules.push_back(new Modules::Dump(args, argv));
    modules.push_back(new Modules::UrlGrabber());
    modules.push_back(new Modules::Repeated(args, argv));

    // Parse args
    NetworkTools::Module* module = parseArguments(args, argv);
    if(!module){
        printHelp();
        exit(-1);
    }

    if(!doesParamExist("-nowarning", args, argv))
        printWarning();

    // Select card
    if(card.empty()){
        networkEngine.selectDefaultDevice();
    }else{
        if(!networkEngine.selectDevice(card)){
            std::cout << "ERROR: Device: " << card << " not found!\n";
            exit(-1);
        }
    }

    // Begin execution
    networkEngine.setupAndBeginPacket(module, 10);

    return 0;
}

// Parse args
NetworkTools::Module* parseArguments(int args, char* argv[]){
    if(args < 2){
        std::cout << ">>> ERROR: No module selected! <<<\n";
        return nullptr;
    }

    // Help stuff
    if(strcmp(argv[1], "help") == 0){
        if(args > 2){
            for(int i = 0; i < modules.size(); i++){
                if(strcmp(modules[i]->getModuleName().c_str(), argv[2]) == 0){
                    modules[i]->printHelp();
                    exit(0);
                }
            }
        }
        std::cout << "No help found!\n";
        exit(-1);
    }
    
    // Get module
    NetworkTools::Module* module = nullptr;
    for(int i = 0; i < modules.size(); i++){
        if(strcmp(modules[i]->getModuleName().c_str(), argv[1]) == 0){
            module = modules[i];
        }
    }

    // Get params
    card = getParam("-device", args, argv);

    return module;
}

// Print help
void printHelp(){
    std::cout << "================================================\n";
    std::cout << "NetworkTools - Copyright (C) 2026 Electro-Corp\n";
    std::cout << "Usage: ./networkTools [module] [optional]\n";
    std::cout << "================================================\n";
    std::cout << "Modules (for help with a module use `help [module]`): \n";
    for(auto& mod : modules) std::cout << "> " << mod->getModuleName() << "\n";
    std::cout << "================================================\n";
    std::cout << "Options: \n";
    std::cout << "-device [deviceName]  Select Specfic Device\n";
    std::cout << "================================================\n";
}

// Print warning
void printWarning(){
    std::cout << "================================================\n";
    std::cout << "NetworkTools - Copyright (C) 2026 Electro-Corp\n";
    std::cout << "WARNING: This program may be illegal to run on \n";
    std::cout << "         networks you don't have permission to \n";
    std::cout << "         run it on.\n";
    std::cout << "         I couldn't care less what happens \n";
    std::cout << "         to you, you are on your own!\n";
    std::cout << "(use -nowarning to disable this message)\n";
    std::cout << "================================================\n";
    std::cout << "\n Press [enter] to affirm...";
    getchar();
}

void setupSignals(){
    signal(SIGINT, interruptSignal);
    signal(SIGSEGV, segfaultSignal);
}

void segfaultSignal(int){
    std::cout << "\nERROR: Segmentation Fault. Goodbye...\n";
    exit(-1);
}

void interruptSignal(int){
    std::cout << "\nInterrupted! Goodbye...\n";
    cleanup();
    exit(-1);
}

// Clean up!
void cleanup(){
    networkEngine.getSelectedModule()->onClose();
    for(int i = 0; i < modules.size(); i++){
        delete modules[i];
    }
}