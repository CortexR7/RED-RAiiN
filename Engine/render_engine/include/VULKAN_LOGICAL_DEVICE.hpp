#ifndef VULKAN_LOGICAL_DEVICE_HPP
#define VULKAN_LOGICAL_DEVICE_HPP

#include <vulkan/vulkan.h>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <WINDOW.hpp>
#include <VULKAN_QUEUE.hpp>
#include <vector>

#define DEBUG_ON
#include <ETL.hpp>


class VULKAN_LOGICAL_DEVICE{
    private:
    VkDevice DEVICE;


    public:
    QUEUE VK_QUEUE;
    void INIT(VULKAN_PHYSICAL_DEVICE PH_DEVICE, WINDOW WIN, std::vector<const char*> deviceExtensions, const std::vector<const char*> validationLayers, bool foo);
    void FREE();
    void RESUME_AFTER_STALL();  // stalls the code until the logical device reaches idle.

    VkDevice GET_HANDLE_TO_VK_LOGICAL_DEVICE();
};

#endif
