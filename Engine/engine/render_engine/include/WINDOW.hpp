#ifndef WINDOW_HEADER_HPP
#define WINDOW_HEADER_HPP

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

/*
*   Copyright (c) 2026 CortexR7
*
*   This class is supposed to manage all byitself the GLFW window
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
    uint32_t width = 600;
    uint32_t height = 600;

    public:
    // Setters and Getters

    void setWindow(GLFWwindow* window);
    void setSurface(VkSurfaceKHR surface);
    void setHeight(uint16_t height);
    void setWidth(uint16_t width);

    GLFWwindow* getWindow();
    VkSurfaceKHR getSurface();
    uint16_t getWIdth();
    uint16_t getHeight();


    // constructor and destructor
    WINDOW();
    ~WINDOW();

    // Member functions
    void INIT_WINDOW();
    void WINDOW_LOOP();
};

#endif
