# Network Tools
An easily extendable program that allows for network analysis. Utilizes `libpcap` (so install it).
This program is for research purposes only.
<br>
## Usage
```
./networkTools [module] [options]
or
./networkTools help [module]
```
<br>
Included modules:
1. `dump` - Dump all traffic through a selected device
2. `urlgrabber` - Grab and display all URLs from packet payload
3. `repeated` - Find patterns in payload

## Modules 
You can write your own modules. Take a look at `src/modules/module_dump.cpp` for a simple example. 

Required functions to implement:
```
void handlePacket(const struct pcap_pkthdr* header, const uint8_t* packet);

void printHelp();
```
Optional:
```
void onClose();
```

