#include "module_urlgrab.hpp"

Modules::UrlGrabber::UrlGrabber() : NetworkTools::Module::Module("urlgrabber"){

}

void Modules::UrlGrabber::handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet){
    std::string url = "";

    // Time stamp
    struct tm ltime;
    char timestr[16];
    time_t local_tv_sec;
    local_tv_sec = header->ts.tv_sec;
    localtime_r(&local_tv_sec, &ltime);
    strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);
    
    // Get payload size
    int ipHeadLen = (((*(packet + 14)) & 0x0F) * 4);
    int tcpHeadLen = (((*(packet + 14 + ipHeadLen + 12)) & 0xF0) >> 4) * 4;
    int totalHeadLen = 14 + ipHeadLen + tcpHeadLen;

    int payloadSize = header->caplen - totalHeadLen;

    if(payloadSize > 0){
        // Copy payload
        uint8_t* payloadData = (uint8_t*)malloc(payloadSize);      
        const uint8_t* ptr = packet + totalHeadLen;
        memcpy(payloadData, ptr, payloadSize);

        // Parse payload
        char http[5] = "http";
        int start = -1, dot = 0;
        for(int i = 0; i < payloadSize - 4; i+=4){
            char tmp[5];
            memcpy(&tmp, payloadData + i, 4);
            if(strcmp(http, tmp) == 0){
                start = i;
                break;
            }
        }
        if(start != -1){
            // Copy URL
            for(int i = start; i < payloadSize; i++){
                dot += payloadData[i] == '.';
                if(dot > 1) break;
                url+= payloadData[i];
            }

            if(!url.empty()){
                std::cout << "[" << timestr << "] " << url << "\n";
                urls.push_back(url);
            }
        }

        free(payloadData);
    }
}

void Modules::UrlGrabber::printHelp(){
    std::cout << "urlgrabber - Module for grabbing urls from packet data\n";
    std::cout << "           > no options\n";
}