#include <RENDER_ENGINE2.hpp>
#define DEBUG_ON
#include <ETL.hpp>


void RENDER_ENGINE2::INIT_ENGINE()
{
    VK_INSTANCE.INIT_INSTANCE();
    DEBUG_LOG("Vulkan instance created successfully!");
    MAIN_WINDOW.INIT_WINDOW(this->VK_INSTANCE);
    DEBUG_LOG("Main window initialized!");
    VKP_DEVICE.INIT_DEVICE(this->MAIN_WINDOW, this->VK_INSTANCE);
    DEBUG_LOG("Vulkan physical device initialized!");
    VKL_DEVICE.INIT(this->VKP_DEVICE, MAIN_WINDOW, this->deviceExtensions, this->validationLayers, false); // ! WARNING ! need to figure out why thE "false" is wrong later 
    DEBUG_LOG("Vulkan logical device initialized!");
    VK_SWAPCHAIN.INIT(MAIN_WINDOW, VKP_DEVICE, VKL_DEVICE);
    DEBUG_LOG("Vulkan swapchain initialized!");
}

void RENDER_ENGINE2::RUN_ENGINE()
{
    MAIN_WINDOW.WINDOW_LOOP();
}

void RENDER_ENGINE2::FREE_ENGINE()
{
    VK_SWAPCHAIN.FREE();
    MAIN_WINDOW.FREE(VK_INSTANCE);
    VKL_DEVICE.FREE();
    VK_INSTANCE.FREE();
}

RENDER_ENGINE2::RENDER_ENGINE2()
{
    this->INIT_ENGINE();
}

RENDER_ENGINE2::~RENDER_ENGINE2()
{
    this->FREE_ENGINE();
}