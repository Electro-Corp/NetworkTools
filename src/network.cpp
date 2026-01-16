#include "network.hpp"

NetworkTools::NetworkEngine::NetworkEngine(){
    populateDevices();
}

void NetworkTools::NetworkEngine::selectDefaultDevice(){
    device = devices;
}

int NetworkTools::NetworkEngine::selectDevice(std::string name){
    for(device = devices; device != NULL; device = device->next){
        if(strcmp(device->name, name.c_str()) == 0) return 1;
    }
    return -1;
}

void NetworkTools::NetworkEngine::printDeviceNames(){
    std::cout << "Devices: ";
    for(device = devices; device != NULL; device = device->next){
        std::cout << device->name << " ";
    }
    std::cout << "\n";
}

// Setup packet handling
void NetworkTools::NetworkEngine::setupAndBeginPacket(NetworkTools::Module* module, int time){
    this->module = module;

    char error[PCAP_ERRBUF_SIZE];

    std::cout << "Starting capture and analysis on device " << device->name << ".\n";
    
    liveDev = pcap_open_live(
        device->name,
        BUFSIZ,
        1,
        time,
        error
    );

    if(!liveDev){
        std::cout << "ERROR: " << error << "\n";
        exit(-1);
    }

    pcap_set_timeout(liveDev, time); // make time config
    pcap_loop(liveDev, 0, &(NetworkTools::NetworkEngine::handlePacket), reinterpret_cast<u_char*>(this));
}

//
// INTERNAL
//

// Populate devices list
void NetworkTools::NetworkEngine::populateDevices(){
    char errorBuffer[PCAP_ERRBUF_SIZE];
    if(pcap_findalldevs(&devices, errorBuffer) == -1){
        std::cout << "ERROR: Populating devices failed: " << errorBuffer << "!\n";
        exit(-1);
    }
}

// Packet handling
void NetworkTools::NetworkEngine::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    this->module->handlePacket(header, packet);
}

// Static packet handling for pcap since its a C library
void NetworkTools::NetworkEngine::handlePacket(u_char* user, const struct pcap_pkthdr* header, const uint8_t* packet){
    reinterpret_cast<NetworkTools::NetworkEngine*>(user)->handlePacket(header, packet); 
}
