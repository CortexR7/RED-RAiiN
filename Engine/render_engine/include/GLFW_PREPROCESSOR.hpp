#ifndef GLFW_PREPROCESSOR_HPP
#define GLFW_PREPROCESSOR_HPP


#include <GLFW/glfw3.h>

// required preprocessor logic to expose proper header based on current OS
#ifdef _WIN32
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WIN32_KHR
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#elif __linux__
    #define GLFW_INCLUDE_VULKAN
    #define VK_USE_PLATFORM_WAYLAND_KHR
    #define GLFW_EXPOSE_NATIVE_WAYLAND
    #include <GLFW/glfw3native.h>
#endif

#endif