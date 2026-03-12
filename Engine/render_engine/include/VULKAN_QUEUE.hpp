#ifndef VULKAN_QUEUE_HPP
#define VULKAN_QUEUE_HPP

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class QUEUE{
    public:
    VkQueue PRESENT_QUEUE;
    VkQueue GRAPHICS_QUEUE;
    
    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device, VkSurfaceKHR& surface);
};

#endif