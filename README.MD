# Network Tools
An easily extendable program that allows for network analysis. Utilizes `libpcap` (so install it).
This could be illegal to run on networks you don't own. I am not responsible for anything you do with this software. 
<br>
Usage:
```
./networkTools [module] [options]
```

## Modules 
You can write your own modules. Take a look at `src/modules/module_dump.cpp` for a simple example. 
<br>
Included modules:
1. Dump - Dump all traffic through a selected device
2. Urlgrabber - Grab and display all URLs from packet payload

<br>
I would've liked doing this in C but C++ makes it easier to make abstractable modules.