#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <VULKAN_QUEUE.hpp>
#include <iostream>


static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
    QueueFamilyIndices indices = QUEUE::findQueueFamilies(device, surface);

    return indices.isComplete() && true; // isSwapChainSuitable(device, surface);    WARNING SWAPCHAIN CHECK WILL COME IN FUTURE
}

void VULKAN_PHYSICAL_DEVICE::INIT_DEVICE(WINDOW& WIN, VULKAN_INSTANCE& INSTANCE)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(INSTANCE.getInstance(), &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find devices with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(INSTANCE.getInstance(), &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device, WIN.getSurface())) {
            this->PH_DEVICE = device;
            break;
        }
    }

    if (this->PH_DEVICE == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}


VkPhysicalDevice VULKAN_PHYSICAL_DEVICE::GET_VK_HANDLE_TO_DEVICE()
{
    return this->PH_DEVICE;
}