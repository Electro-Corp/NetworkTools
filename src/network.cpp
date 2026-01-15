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


// Populate devices list
void NetworkTools::NetworkEngine::populateDevices(){
    char errorBuffer[PCAP_ERRBUF_SIZE];
    if(pcap_findalldevs(&devices, errorBuffer) == -1){
        std::cout << "ERROR: Populating devices failed: " << errorBuffer << "!\n";
        exit(-1);
    }
}