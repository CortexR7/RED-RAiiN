#include <WINDOW.hpp>


// Setters and Getters

void WINDOW::setSurface(VkSurfaceKHR surface)
{
    this->surface = surface;
}

void WINDOW::setWindow(GLFWwindow* window)
{
    this->window = window;
}


VkSurfaceKHR WINDOW::getSurface()
{
    return this->surface;
}

GLFWwindow* WINDOW::getWindow()
{
    return this->window;
}



// constructor and destructor
WINDOW::WINDOW(){}
WINDOW::~WINDOW(){}