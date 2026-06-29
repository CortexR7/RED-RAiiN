#ifndef DEBUG_LOG_HPP
#define DEBUG_LOG_HPP
#include <string>
#include <iostream>
                                    // NOTE: If DEBUG_ON Macro is defined bfore the inlusion of the header then DEBUG_LOG will be enabled
#if defined(DEBUG_ON)
#define DEBUG_LOG(message) do { \
    std::cout << "[DEBUG] \033[33m" << message << "\033[0m" << std::endl; \
} while(0)

#define DEBUG_ERR(message) do { \
    std::cout << "[DEBUG-ERR] \033[31m" << message << "\033[0m" << std::endl; \
} while(0)

#else
#define DEBUG_LOG(message) do {} while(0)
#define DEBUG_ERR(message) do {} while(0)


#endif
#endif