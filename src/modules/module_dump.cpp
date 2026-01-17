#include "module_dump.hpp"

Modules::Dump::Dump(int args, char* argv[]) : NetworkTools::Module::Module("dump"){
    dumpPackets = doesParamExist("-payload", args, argv);
}

void Modules::Dump::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    // Time stamp
    struct tm ltime;
    char timestr[16];
    time_t local_tv_sec;
    local_tv_sec = header->ts.tv_sec;
    localtime_r(&local_tv_sec, &ltime);
    strftime( timestr, sizeof timestr, "%H:%M:%S", &ltime);

    // Convert to ether_header
    struct ether_header* eth_head =(struct ether_header*) packet;

    // Get packet type
    std::string packetType = "Undefined";
    int ipPacket = 0;
    switch(ntohs(eth_head->ether_type)){
        case ETHERTYPE_IP:
            ipPacket = 1;
            packetType = "IP";
            break;
        case ETHERTYPE_ARP:
            packetType = "ARP";
            break;
        case ETHERTYPE_REVARP:
            packetType = "REVARP";
            break;
        case ETHERTYPE_IPV6:
            ipPacket = 1;
            packetType = "IPV6";
            break;
    }

    // Get targets from and to
    struct in_addr address;
    memcpy(&(address.s_addr), eth_head->ether_shost, sizeof(struct in_addr));
    std::string sHost = inet_ntoa(address);
    memcpy(&(address.s_addr), eth_head->ether_dhost, sizeof(struct in_addr));
    std::string dHost = inet_ntoa(address);
    
    // Get payload size
    int ipHeadLen = (((*(packet + 14)) & 0x0F) * 4);
    int tcpHeadLen = (((*(packet + 14 + ipHeadLen + 12)) & 0xF0) >> 4) * 4;
    int totalHeadLen = ipHeadLen + tcpHeadLen;

    int payloadSize = header->caplen - totalHeadLen;

    // Copy payload
    char payloadData[payloadSize];
    const uint8_t* ptr = (packet + totalHeadLen);
    memcpy(&payloadData, ptr, payloadSize);

    // Print out data
    std::cout << "[" << timestr << "] Packet (" << packetType << ") length: " << std::to_string(header->len) << "\n";
    std::cout << "           From " << sHost << " to " << dHost << "\n";
    
    if(dumpPackets){
        std::cout << "           Payload (size " << payloadSize << "):\n";
        for(int i = 0; i < payloadSize; i++){
            if(i % 15 == 0){
                printf("\n           ");
            }
            if(payloadData[i])
                printf("%c", (char)payloadData[i]);
            else printf("?");
        }
        printf("\n");
    }
    
}

void Modules::Dump::printHelp(){
    std::cout << "dump - dump all raw network traffic\n";
    std::cout << "      > Options:\n";
    std::cout << "        -payload     Show packet payload\n";
    //std::cout << ""
}