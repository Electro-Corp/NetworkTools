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

#define HAVE_REMOTE
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <sys/types.h>
#include <net/ethernet.h>

namespace NetworkTools{
    class NetworkEngine{
    private:
        pcap_if_t* devices;
        pcap_if_t* device;    
        
        // Populate devices list
        void populateDevices();
    public:
        NetworkEngine();

        void selectDefaultDevice();
        int selectDevice(std::string name);

        void printDeviceNames();

        // Getters
        pcap_if_t* getSelectedDevice(){
            return device;
        }
    };
} // NetworkTools