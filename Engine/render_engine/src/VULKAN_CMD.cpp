#include <VULKAN_CMD.hpp>


void VULKAN_CMD::INIT(VULKAN_PHYSICAL_DEVICE& PH_DEVICE, WINDOW& WIN, VULKAN_LOGICAL_DEVICE& LG_DEVICE)
{
    VkPhysicalDevice vkPhysicalDevice = PH_DEVICE.GET_VK_HANDLE_TO_DEVICE();
    QueueFamilyIndices queueFamilyIndices = QUEUE::findQueueFamilies(vkPhysicalDevice, WIN.getSurface());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if(vkCreateCommandPool(LG_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &poolInfo, nullptr, &CMD_POOL_GRAPHICS) != VK_SUCCESS) {
        DEBUG_LOG("FAILED TO CREATE COMMAND POOL !!!");
        throw std::runtime_error("failed to create command pool!");
    } else {
        DEBUG_LOG("COMMAND POOL CREATED SUCCESSFULLY !!!");
    }
}

void VULKAN_CMD::FREE(VULKAN_LOGICAL_DEVICE& LG_DEVICE)
{
    vkDestroyCommandPool(LG_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->CMD_POOL_GRAPHICS, nullptr);
}   