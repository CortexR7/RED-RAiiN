#ifndef VULKAN_DESC_SET_HPP
#define VULKAN_DESC_SET_HPP

#include <cstdint>
#include <vulkan/vulkan.h>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <RE2_UNIFORM_BUFFER_OBJECT.hpp>


class VULKAN_DESC_SET{
    public:
        uint32_t DESC_COUNT;
        VULKAN_LOGICAL_DEVICE INTERNAL_LGD;
        VkDescriptorSetLayout DESCRIPTOR_SET_LAYOUT;
        VkDescriptorPool DESCRIPTOR_POOL;
        std::vector<VkDescriptorSet> DESCRIPTOR_SETS;

        void INIT_DESC_POOL(uint32_t DESC_COUNT);

    public:
        void INIT(VULKAN_LOGICAL_DEVICE LGD, uint32_t DESC_COUNT);
        void UPDATE_SETS(RE2_UBO_OBJ& UBO);
        void FREE();
};

#endif
