#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <iostream>


void VULKAN_LOGICAL_DEVICE::INIT(
    VULKAN_PHYSICAL_DEVICE PH_DEVICE, 
    WINDOW WIN, 
    std::vector<const char*> const deviceExtensions, 
    const std::vector<const char*> validationLayers,
    bool foo
)
{
    VkPhysicalDevice p_device = PH_DEVICE.GET_VK_HANDLE_TO_DEVICE();
    VkSurfaceKHR surface = WIN.getSurface();
    QueueFamilyIndices indices = QUEUE::findQueueFamilies(p_device, surface);
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    // empty device features for now
    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (foo) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }    

    if(vkCreateDevice(p_device, &createInfo, nullptr, &DEVICE) != VK_SUCCESS){
        throw std::runtime_error("failed to create a logical Device!");
    } else{
        vkGetDeviceQueue(DEVICE, indices.graphicsFamily.value(), 0, &(this->VK_QUEUE.GRAPHICS_QUEUE));
        vkGetDeviceQueue(DEVICE, indices.presentFamily.value(), 0, &(this->VK_QUEUE.PRESENT_QUEUE));
    }
}

void VULKAN_LOGICAL_DEVICE::FREE()
{
    vkDestroyDevice(this->DEVICE, nullptr);
}

VkDevice VULKAN_LOGICAL_DEVICE::GET_HANDLE_TO_VK_LOGICAL_DEVICE()
{
    return this->DEVICE;
}