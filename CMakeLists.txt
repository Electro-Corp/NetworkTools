cmake_minimum_required(VERSION 3.10)

project(networkTools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find libpcap
find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

# Create executable
add_executable(networkTools
    # Base module class
    src/module.cpp
    # Individual modules
    src/modules/module_dump.cpp
    # Main
    src/network.cpp
    src/main.cpp
)

# Include libpcap headers
target_include_directories(networkTools PRIVATE
    ${PCAP_INCLUDE_DIRS}
)

# Link libpcap
target_link_libraries(networkTools PRIVATE 
    ${PCAP_LIBRARIES}
)

target_compile_options(networkTools PRIVATE
    ${PCAP_CFLAGS_OTHER}
    -g
)
