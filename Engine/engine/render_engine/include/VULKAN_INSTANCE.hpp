#ifndef VULKAN_INSTANCE_HPP
#define VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <vector>
#include <GLFW_PREPROCESSOR.hpp>


class VULKAN_INSTANCE{

    private:
    VkInstance INSTANCE{};
    bool DEBUG = true;
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    VkDebugUtilsMessengerEXT DEBUG_MESSENGER{};
    void setupDebugMessengerValidation(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);

    // private helper methods
    std::vector<const char*> getRequiredExtensions();

    public:
    VkInstance& getInstance();
    void INIT_INSTANCE();

    void FREE();
};

#endif