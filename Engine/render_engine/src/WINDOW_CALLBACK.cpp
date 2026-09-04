#include <WINDOW.hpp>
#include <functional>


void WINDOW::FRAMEBUFFER_SIZE_CALLBACK(GLFWwindow* window, int width, int height)
{
    WINDOW* WINDOW_OBJECT_PTR = reinterpret_cast<WINDOW*>(glfwGetWindowUserPointer(window));
    WINDOW_OBJECT_PTR->FRAMEBUFFER_SIZE_CALLBACK_IMPL(width, height);
}

void WINDOW::SETUP_CALLBACK_FUNCTIONS()
{
    glfwSetFramebufferSizeCallback(this->window, this->FRAMEBUFFER_SIZE_CALLBACK);
}
