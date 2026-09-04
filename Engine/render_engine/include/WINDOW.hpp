#ifndef WINDOW_HEADER_HPP
#define WINDOW_HEADER_HPP

#include <vulkan/vulkan.h>
#include <GLFW_PREPROCESSOR.hpp>
#include <VULKAN_INSTANCE.hpp>
#include <functional>

/*
*   Copyright (c) 2026 CortexR7
*
*   This class is supposed to manage all byitself the GLFW window
*/


class WINDOW{

    private:
    GLFWwindow* window;
    VkSurfaceKHR surface;
    uint16_t width = 870;
    uint16_t height = 730;

    static void FRAMEBUFFER_SIZE_CALLBACK(GLFWwindow* window, int width, int height);
    void SETUP_CALLBACK_FUNCTIONS();

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


    // WARNING: Belowe this section there will be the std::functions that will store the actual implementtation for the
    // callback functions
    std::function<void(int, int)> FRAMEBUFFER_SIZE_CALLBACK_IMPL; // USAGE: FRAMEBUFFER_SIZE_CALLBACK_IMPL(width, height)


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
