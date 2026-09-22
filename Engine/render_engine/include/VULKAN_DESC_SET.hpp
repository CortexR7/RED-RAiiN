#ifndef VULKAN_DESC_SET_HPP
#define VULKAN_DESC_SET_HPP

/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the VK DESC_SET.
*  It represents an object that does follwing things:
*
*  - It stores descriptors sets of "DESC_COUNT"
*  - It stores the descriptor pool from where th sets get allocated
*  - It stores exacltly ONE descriptor set layout (all other x amount of descripto sets are based on that layout.) x = DESC_SET
*
*/

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
        void UPDATE_SETS(RE2_UBO_OBJ& UBO);                         // WARNING: Its is probably good to mention that the UBO passed here MUST
        void FREE();                                                // have a UBO_COUNT that matches the DESC_COUNT. Else a segfault will occur due to
};                                                                  // an out of bounds exception if DESC_COUNT > UBO_COUNT.

#endif
