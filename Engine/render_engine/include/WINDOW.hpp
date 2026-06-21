#ifndef WINDOW_HEADER_HPP
#define WINDOW_HEADER_HPP

#include <vulkan/vulkan.h>
#include <GLFW_PREPROCESSOR.hpp>
#include <VULKAN_INSTANCE.hpp>

/*
*   Copyright (c) 2026 CortexR7
*
*   This class is supposed to manage all byitself the GLFW window
*/


class WINDOW{

    private: 
    GLFWwindow* window;    
    VkSurfaceKHR surface;
    uint16_t width = 600;
    uint16_t height = 600;

    public:
    // Setters and Getters

    void setWindow(GLFWwindow* window);
    void setSurface(VkSurfaceKHR surface);
    void setHeight(uint16_t height);
    void setWidth(uint16_t width);

    GLFWwindow* getWindow();
    VkSurfaceKHR& getSurface();
    uint16_t getWidth();
    uint16_t getHeight();


    // constructor and destructor
    WINDOW();
    ~WINDOW();

    // Member functions
    void INIT_WINDOW(VULKAN_INSTANCE& INSTANCE);
    void WINDOW_LOOP();
    void WINDOW_LOOP(void (*FUNC_PTR)(void));

    void FREE(VULKAN_INSTANCE& INSTNACE);
};

#endif
