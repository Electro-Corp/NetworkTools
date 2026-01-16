/*
    NetworkTools - Network Analysis Tool
    module.hpp - Abstract header for analysis tools

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

#include "network.hpp"

#include <string>

namespace NetworkTools{
    class Module {
    private:
        std::string moduleName;
    public:
        Module(std::string moduleName);

        virtual void handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet) = 0;

        // Getters
        std::string getModuleName(){
            return moduleName;
        }
    };
} // NetworkTools