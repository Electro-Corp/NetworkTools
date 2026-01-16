#include "module_dump.hpp"

Modules::Dump::Dump() : NetworkTools::Module::Module("dump"){

}

void Modules::Dump::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    // Time stamp
    struct tm ltime;
    char timestr[16];
    time_t local_tv_sec;
    local_tv_sec = header->ts.tv_sec;
    localtime_s(&ltime, &local_tv_sec);
    strftime( timestr, sizeof timestr, "%H:%M:%S", &ltime);

    // Print out data
    std::cout << "[" << timestr << "] Packet length: " << std::to_string(header->len) << "\n";
}