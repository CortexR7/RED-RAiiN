#ifndef VULKAN_CMD_HPP
#define VULKAN_CMD_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <VULKAN_QUEUE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <WINDOW.hpp>
#include <VULKAN_LOGICAL_DEVICE.hpp>

#define DEBUG_ON            // NOTE: comment this line out to disable debug logs for "VULKAN_CMD.cpp"
#include <ETL.hpp>



class VULKAN_CMD{
    public:
    VkCommandPool CMD_POOL_GRAPHICS;
    std::vector<VkCommandBuffer> CMD_BUFFERS_GRAPHICS;

    void INIT(VULKAN_PHYSICAL_DEVICE& PH_DEVICE, WINDOW& WIN, VULKAN_LOGICAL_DEVICE& LG_DEVICE);
    void FREE(VULKAN_LOGICAL_DEVICE& LG_DEVICE);
};


#endif