#ifndef WINDOW_HEADER_HPP
#define WINDOW_HEADER_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

/*
*   Copyright (c) 2026 CortexR7
*
*   This class is supposed to manage all byitself the GLFW window
*   and the Vulkan window surface.
*/


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


class WINDOW{
    private: 
    GLFWwindow* window;    
    VkSurfaceKHR surface;

    public:
    // Setters and Getters

    void setWindow(GLFWwindow* window);
    void setSurface(VkSurfaceKHR surface);

    GLFWwindow* getWindow();
    VkSurfaceKHR getSurface();


    // constructor and destructor
    WINDOW();
    ~WINDOW();
};

#endif
