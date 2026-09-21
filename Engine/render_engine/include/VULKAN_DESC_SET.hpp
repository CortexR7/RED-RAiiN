#ifndef VULKAN_DESC_SET_HPP
#define VULKAN_DESC_SET_HPP

#include <vulkan/vulkan.h>
#include <VULKAN_LOGICAL_DEVICE.hpp>

class VULKAN_DESC_SET{
    private:
        VULKAN_LOGICAL_DEVICE INTERNAL_LGD;
        VkDescriptorSetLayout DESCRIPTOR_SET_LAYOUT;

    public:
        void INIT(VULKAN_LOGICAL_DEVICE LGD);
        void FREE();
};

#endif
