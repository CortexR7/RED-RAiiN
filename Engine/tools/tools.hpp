#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>

/* 
* Copyright (c) 2025 CortexR7
*
* This header defines a set of functions that can be used for easy development
* functions that are rather OS specific might fall under a custom namespace that might be added later on.
*/


namespace tools{
    
    #ifdef LOGGER_ON
    #define LOG(msg) std::cout << "\033[33m" << "[LOGGER]: " << msg << "\033[0m" << std::endl;
    #else    
    #define LOG(msg) 
    #endif
}

#endif
