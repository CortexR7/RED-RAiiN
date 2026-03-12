#ifndef VULKAN_LOGICAL_DEVICE_HPP
#define VULKAN_LOGICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <WINDOW.hpp>
#include <VULKAN_QUEUE.hpp>
#include <vector>


class VULKAN_LOGICAL_DEVICE{
    private:
    VkDevice DEVICE;
    QUEUE VK_QUEUE;

    public:
    void INIT(VULKAN_PHYSICAL_DEVICE PH_DEVICE, WINDOW WIN, std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers, bool foo);
    void FREE();
};

#endif