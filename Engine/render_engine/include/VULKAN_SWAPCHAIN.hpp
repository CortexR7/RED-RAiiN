#ifndef VULKAN_SWAPCHAIN_HPP
#define VULKAN_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <WINDOW.hpp>
#include <VULKAN_LOGICAL_DEVICE.hpp>

// This is needed since max and min are macros that comes with windows.h
// These override the std::max and std::min functions from <algorithm>
// and then cause compilation errors
#ifdef _WIN32
#undef max
#undef min
#endif


struct SwapChainSupportDetails{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


class VULKAN_SWAPCHAIN{
    private:
    SwapChainSupportDetails SW_CHAIN_SUPPORT;
    VULKAN_LOGICAL_DEVICE LG_DEVICE;
    VkExtent2D SW_CHAIN_RESOLUTION;
    VkFormat SW_CHAIN_IMAGE_FORMAT;


    SwapChainSupportDetails querySwapChainSupport(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE);
    bool isSwapChainSuitable(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE);


    public:
    VkSwapchainKHR SW_CHAIN;
    VkExtent2D GET_SWAPCHAIN_RESOLUTION();
    VkFormat GET_SWAPCHAIN_IMAGE_FORMAT();
    std::vector<VkFramebuffer> SW_CHAIN_FRAMEBUFFERS;
    std::vector<VkImage> SW_CHAIN_IMAGES;
    std::vector<VkImageView> SW_CHAIN_IMAGE_VIEWS;


    void INIT(WINDOW WIN, VULKAN_PHYSICAL_DEVICE PH_DEVICE, VULKAN_LOGICAL_DEVICE LG_DEVICE);
    void FREE();
};

#endif