#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <VULKAN_QUEUE.hpp>
#include <iostream>


static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
    QueueFamilyIndices indices = QUEUE::findQueueFamilies(device, surface);

    bool DRIVER_API_SUPPRT = false;
    VkPhysicalDeviceProperties PH_DEVICE_PROPS{};
    vkGetPhysicalDeviceProperties(device, & PH_DEVICE_PROPS);
    if(PH_DEVICE_PROPS.apiVersion < VK_API_VERSION_1_3)
    {
        DRIVER_API_SUPPRT = false;
    } else{
        DRIVER_API_SUPPRT = true;
    }

    return indices.isComplete() && DRIVER_API_SUPPRT && true; // isSwapChainSuitable(device, surface);    WARNING SWAPCHAIN CHECK WILL COME IN FUTURE
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
        DEBUG_ERR("NO SUITABLE GPU WAS FOUND EITHER DUE TO MISSING DRIVERS OR SIMPLY OLD HARDWARE WITH NO SUPPORT FOR VULKAN_1.3");
        DEBUG_ERR("IN CASE OF OLD HARDWARE AND NO SUPPORTED DRIVERS BEING AVAILABLE TRY UPDATING DRIVERS");
        DEBUG_ERR("IF THIS DOESNT HELP THEN THE DEVICE IS TOO OLD AND THERE IS NO WAY OF RUNNING THE ENGINE !");
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}


VkPhysicalDevice VULKAN_PHYSICAL_DEVICE::GET_VK_HANDLE_TO_DEVICE()
{
    return this->PH_DEVICE;
}
