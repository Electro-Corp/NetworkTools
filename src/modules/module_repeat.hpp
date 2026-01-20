/*
    NetworkTools - Network Analysis Tool
    module_repeat.hpp - Scan for repeated patterns in packets

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

#include <algorithm>

#include "../module.hpp"
#include "../arguments.hpp"

namespace Modules{
    class Repeated : public NetworkTools::Module{
    private:
        // Config vars
        int maxPacketStore, minCommon;
        //
        std::vector<std::vector<uint8_t>> packetPayloadStore; // 
        std::vector<std::vector<uint8_t>> common;
    public:
        Repeated(int args, char* argv[]);

        void handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet);

        // Add to list (if it holds maxPacketStore remove the oldest)
        void addDataToStore(std::vector<uint8_t> data);

        // Look through last packets and see if we can find anything
        void checkForRepeat();

        void onClose() override;

        void printHelp();
    };
} // Modules