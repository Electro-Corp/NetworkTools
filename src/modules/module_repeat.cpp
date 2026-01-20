#include "module_repeat.hpp"

Modules::Repeated::Repeated(int args, char* argv[]) : NetworkTools::Module("repeated"){
    // Store defaults
    maxPacketStore = 10;
    minCommon = 30;

    // Check if user wants anything
    if(doesParamExist("-maxstore", args, argv)){
        maxPacketStore = std::stoi(getParam("-maxstore", args, argv));
    }
    if(doesParamExist("-mincommon", args, argv)){
        minCommon = std::stoi(getParam("-mincommon", args, argv));
    }

    std::cout << "Storing " << maxPacketStore << " packets and checking for a min of " << minCommon << " common bytes.\n";
}

void Modules::Repeated::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    // Convert to ether_header
    struct ether_header* eth_head = (struct ether_header*) packet;

    // Is it an IP packet
    int cont = eth_head->ether_type == ETHERTYPE_IP || eth_head->ether_type == ETHERTYPE_IPV6;
    //if(!cont) return;
    
    // Get payload size
    int ipHeadLen = (((*(packet + 14)) & 0x0F) * 4);
    int tcpHeadLen = (((*(packet + 14 + ipHeadLen + 12)) & 0xF0) >> 4) * 4;
    int totalHeadLen = ipHeadLen + tcpHeadLen + 14;

    uint8_t payloadSize = header->caplen - totalHeadLen;

    // Copy payload
    std::vector<uint8_t> tmp;
    const uint8_t* ptr = (packet + totalHeadLen);
    for(int i = 0; i < payloadSize; i++){
        tmp.push_back(*ptr++);
    }

    addDataToStore(tmp);

    checkForRepeat();

    std::cout << "Comminalites found: " << common.size() << "\n";
    // for(int i = 0; i < common.size(); i++){
    //     for(int n = 0; n < common[i].size(); n++){
    //         printf("%x ", common[i][n]);
    //     }
    //     printf("\n");
    // }
    // std::cout << "\n";
}

void Modules::Repeated::addDataToStore(std::vector<uint8_t> data){
    packetPayloadStore.push_back(data);
    
    if(packetPayloadStore.size() > maxPacketStore){
        packetPayloadStore.erase(packetPayloadStore.begin());
    }
}

void Modules::Repeated::checkForRepeat(){
    int checking = 0;
    std::vector<uint8_t> data;
    // horrible nasty three nested four loops
    // First vector
    for(int i = 0; i < packetPayloadStore.size(); i++){
        // Second vector
        for(int n = i + 1; n < packetPayloadStore.size(); n++){
            // Check each byte
            for(int g = 0; g < std::min(packetPayloadStore[i].size(), packetPayloadStore[n].size()); g++){
                // See if we can
                if(packetPayloadStore[i][g] == packetPayloadStore[n][g]) checking = 1;
                else checking = 0;
                // Are we currently looking
                if(checking){
                    data.push_back(packetPayloadStore[i][g]);
                }else{
                    if(data.size() > minCommon){
                        if(common.size() > 0){
                            if(std::find(common.begin(), common.end(), data) != common.end()) common.push_back(data);
                        } 
                        else common.push_back(data);
                            
                    }
                    data.clear();
                }
            }
        }
    }
}

void Modules::Repeated::onClose(){
    for(int i = 0; i < common.size(); i++){
        FILE* fp = fopen(std::string{"repeat/" + std::to_string(i)}.c_str(), "w");
        for(int n = 0; n < common[i].size(); n++)
            fwrite(&common[i][n], 1, sizeof(uint8_t), fp);
        fclose(fp);
    }
}

void Modules::Repeated::printHelp(){
    std::cout << "repeated - Find patterns in payload data, and dumps to a directory\n";
    std::cout << "          > Options: \n";
    std::cout << "            -maxstore [number]    How many packets are stored to compare against\n";
    std::cout << "            -mincommon [number]   How many bytes need to be similar to be logged\n";
}