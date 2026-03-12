#include <WINDOW.hpp>
#include <iostream>
#include <string>



// constants only for this TU empty for now

// setters and getters

void WINDOW::setSurface(VkSurfaceKHR surface)
{
    this->surface = surface;
}

void WINDOW::setWindow(GLFWwindow* window)
{
    this->window = window;
}

void WINDOW::setHeight(uint16_t height)
{
    this->height = height;
}

void WINDOW::setWidth(uint16_t width)
{
    this->width = width;
}



VkSurfaceKHR& WINDOW::getSurface()
{
    return this->surface;
}

GLFWwindow* WINDOW::getWindow()
{
    return this->window;
}

uint16_t WINDOW::getHeight(){return this->height;}
uint16_t WINDOW::getWIdth(){return this->width;}


// constructor and destructor
WINDOW::WINDOW(){}
WINDOW::~WINDOW(){}



// functions only visible for the current TU
static void createvksurface(const VkInstance& instance, VkSurfaceKHR& surface, GLFWwindow*& window)
{
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}


// member functions
void WINDOW::INIT_WINDOW(VULKAN_INSTANCE& INSTANCE)
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    this->window = glfwCreateWindow(this->width, this->height, "RED-RAiiN Engine", nullptr, nullptr);

    createvksurface(INSTANCE.getInstance(), this->surface, this->window);
}

void WINDOW::WINDOW_LOOP()
{
    while (!glfwWindowShouldClose(this->window))
    {
        glfwPollEvents();
    }
}

void WINDOW::FREE(VULKAN_INSTANCE& INSTNACE)
{
    vkDestroySurfaceKHR(INSTNACE.getInstance(), this->surface, nullptr);
}