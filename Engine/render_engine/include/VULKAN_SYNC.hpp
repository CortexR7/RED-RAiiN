#ifndef VULKAN_SYNC_HPP
#define VULKAN_SYNC_HPP

#include <vulkan/vulkan.h>
#include <ETL.hpp>


class VULKAN_SYNC{
    public:
    ETL::DYNAMIC_ARRAY<VkSemaphore> SEMAPHORES{1, 1.0f};
    ETL::DYNAMIC_ARRAY<VkFence> FENCES{1, 1.0f};
    VULKAN_SYNC();
};

#endif