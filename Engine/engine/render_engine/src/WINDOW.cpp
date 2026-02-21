#include <WINDOW.hpp>
#include <iostream>
#include <string>



// constants only for this TU
const static std::string WINDOW_OBJ_STRING = "WINDOW_OBJECT: ";

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



VkSurfaceKHR WINDOW::getSurface()
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


// member functions
void WINDOW::INIT_WINDOW()
{
    using namespace std;

    if(glfwInit() == GLFW_FALSE)
    {
        cout << WINDOW_OBJ_STRING << "Failed to init GLFW !\n"; 
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    this->window = glfwCreateWindow(this->width, this->height, "RED-RAiiN Engine", nullptr, nullptr);
}

void WINDOW::WINDOW_LOOP()
{
    while (!glfwWindowShouldClose(this->window))
    {
        glfwPollEvents();
    }
}