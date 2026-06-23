#ifndef VULKAN_SYNC_HPP
#define VULKAN_SYNC_HPP

#include <vulkan/vulkan.h>
#include <ETL.hpp>


class VULKAN_SYNC{
    public:
    ETL::DynamicArray<VkSemaphore> SEMAPHORES{1, 1.0f};
    ETL::DynamicArray<VkFence> FENCES{1, 1.0f};
    VULKAN_SYNC();
};

#endif