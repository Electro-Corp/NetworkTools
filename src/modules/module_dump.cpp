#include "module_dump.hpp"

Modules::Dump::Dump() : NetworkTools::Module::Module("dump"){

}

void Modules::Dump::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    std::cout << "Packet length: " << std::to_string(header->len) << "\n";
}