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

## Modules 
You can write your own modules. Take a look at `src/modules/module_dump.cpp` for a simple example. 
<br>
Included modules:
1. Dump - Dump all traffic through a selected device
2. Urlgrabber - Grab and display all URLs from packet payload
3. Repeated - Find patterns in payload

