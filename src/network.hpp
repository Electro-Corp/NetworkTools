/*
    NetworkTools - Network Analysis Tool
    network.hpp - Header for network engine

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

#include <iostream>
#include <vector>
#include <cstring>
#include <functional>

#define HAVE_REMOTE
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <sys/types.h>
#include <net/ethernet.h>

#include "module.hpp"

namespace NetworkTools{
    class Module; // Forward declare 

    class NetworkEngine{
    private:
        pcap_if_t* devices;
        pcap_if_t* device;   
        
        // Device to capture from
        pcap_t* liveDev;
        // Module to output data to
        NetworkTools::Module* module;
        
        // Populate devices list
        void populateDevices();
        // Packet handling
        void handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet);
        // Static packet handling for pcap since its a C library
        static void handlePacket(u_char*, const struct pcap_pkthdr* header, const uint8_t* packet);
    public:
        NetworkEngine();

        // Setup packet handling
        void setupAndBeginPacket(NetworkTools::Module* module, int time);

        // Device selection
        void selectDefaultDevice();
        int selectDevice(std::string name);

        // Print device name
        void printDeviceNames();

        // Getters
        pcap_if_t* getSelectedDevice(){
            return device;
        }
    };
} // NetworkTools