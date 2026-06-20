#include <VULKAN_SWAPCHAIN.hpp>
#include <limits>
#include <algorithm>
#include <VULKAN_QUEUE.hpp>
#include <iostream>


SwapChainSupportDetails VULKAN_SWAPCHAIN::querySwapChainSupport(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE)
{
    SwapChainSupportDetails details;
    VkPhysicalDevice device = PH_DEVICE.GET_VK_HANDLE_TO_DEVICE();
    VkSurfaceKHR surface = WIN.getSurface();
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
    details.formats.resize(formatCount);
    if(formatCount != 0){
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }
    
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
    details.presentModes.resize(presentModeCount);
    if(presentModeCount != 0){
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }
    
    return details;
}

bool VULKAN_SWAPCHAIN::isSwapChainSuitable(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE)
{
    SwapChainSupportDetails swap_chain_support_details = this->querySwapChainSupport(WIN, PH_DEVICE);
    return (!swap_chain_support_details.formats.empty() && !swap_chain_support_details.presentModes.empty());
}

static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) 
{
    for(auto& availableFormat : availableFormats)
    {
        if(availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }
    
    //---------------WARNING---------------//
    //------THIS-ERR-HANDLING-IS-STUPID----//
    //--------MIGHT-CRASH-THE-SYSTEM-------//
    return availableFormats[0];
}

static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) 
{
    for(auto& availablePresentMode : availablePresentModes)
    {
        if(availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

static VkExtent2D chooseSwapExtent(GLFWwindow*& window, const VkSurfaceCapabilitiesKHR& capabilities) 
{
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);      
    VkExtent2D actualExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}

VkExtent2D VULKAN_SWAPCHAIN::GET_SWAPCHAIN_RESOLUTION()
{
    return this->SW_CHAIN_RESOLUTION;
}

VkFormat VULKAN_SWAPCHAIN::GET_SWAPCHAIN_IMAGE_FORMAT()
{
    return this->SW_CHAIN_IMAGE_FORMAT;
}

void VULKAN_SWAPCHAIN::INIT(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE, VULKAN_LOGICAL_DEVICE LG_DEVICE)
{
    this->LG_DEVICE = LG_DEVICE;
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(WIN, PH_DEVICE);
    GLFWwindow* win = WIN.getWindow();

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(win, swapChainSupport.capabilities);
    SW_CHAIN_RESOLUTION = extent;
    SW_CHAIN_IMAGE_FORMAT = surfaceFormat.format;

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;  // higher values here probably wont result in more images since the capabilities are usually only up to 3 for tripple buffering.

    if(swapChainSupport.capabilities.maxImageCount != 0 && imageCount > swapChainSupport.capabilities.maxImageCount)    // 0 mean there is no maximum Image count !
    {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = WIN.getSurface();
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    VkPhysicalDevice device = PH_DEVICE.GET_VK_HANDLE_TO_DEVICE();
    VkSurfaceKHR surface = WIN.getSurface();
    QueueFamilyIndices indices = QUEUE::findQueueFamilies(device, surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // set this to opaque with this flag "VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR"
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;


    if(vkCreateSwapchainKHR(LG_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &createInfo, nullptr, &(this->SW_CHAIN)) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create a swapchain !");
    }
}

void VULKAN_SWAPCHAIN::FREE()
{
    vkDestroySwapchainKHR(this->LG_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->SW_CHAIN, nullptr);
}