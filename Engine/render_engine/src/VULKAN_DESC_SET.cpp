#include <cstdint>
#include <vulkan/vulkan.h>
#include <VULKAN_DESC_SET.hpp>

#define DEBUG_ON
#include <ETL.hpp>

void VULKAN_DESC_SET::INIT(VULKAN_LOGICAL_DEVICE LGD, uint32_t DESC_COUNT)
{
    this->DESC_COUNT = DESC_COUNT;
    this->INTERNAL_LGD = LGD;
    VkDescriptorSetLayoutBinding UBO_LAYOUT_BINDING{};
    UBO_LAYOUT_BINDING.binding = 0;
    UBO_LAYOUT_BINDING.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    UBO_LAYOUT_BINDING.descriptorCount = 1;
    UBO_LAYOUT_BINDING.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    UBO_LAYOUT_BINDING.pImmutableSamplers = nullptr;


    VkDescriptorSetLayoutCreateInfo LAYOUT_INFO{};
    LAYOUT_INFO.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;;
    LAYOUT_INFO.bindingCount = 1;
    LAYOUT_INFO.pBindings = &UBO_LAYOUT_BINDING;

    if(vkCreateDescriptorSetLayout(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &LAYOUT_INFO, nullptr, &this->DESCRIPTOR_SET_LAYOUT) != VK_SUCCESS)
    {
        DEBUG_ERR("SUCCESSFULY created descriptor layout");
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    DEBUG_LOG("Created Descriptor set layout for UBO");

    this->INIT_DESC_POOL(DESC_COUNT);
}

void VULKAN_DESC_SET::INIT_DESC_POOL(uint32_t DESC_COUNT)
{
    VkDescriptorPoolSize POOL_SIZE{};
    POOL_SIZE.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    POOL_SIZE.descriptorCount = static_cast<uint32_t>(DESC_COUNT);

    VkDescriptorPoolCreateInfo POOL_INFO{};
    POOL_INFO.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    POOL_INFO.poolSizeCount = 1;
    POOL_INFO.pPoolSizes = &POOL_SIZE;
    POOL_INFO.maxSets = static_cast<uint32_t>(DESC_COUNT);

    if (vkCreateDescriptorPool(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &POOL_INFO, nullptr, &this->DESCRIPTOR_POOL) != VK_SUCCESS) {
        DEBUG_ERR("Failed to create Descriptor pool !");
        throw std::runtime_error("failed to create descriptor pool!");
    }
    this->DESCRIPTOR_SETS.resize(DESC_COUNT);
    DEBUG_LOG("SUCCESSFULLY created Descriptor pool");


    std::vector<VkDescriptorSetLayout> LAYOUTS(DESC_COUNT, this->DESCRIPTOR_SET_LAYOUT);
    VkDescriptorSetAllocateInfo ALLOC_INFO{};
    ALLOC_INFO.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    ALLOC_INFO.descriptorPool = this->DESCRIPTOR_POOL;
    ALLOC_INFO.descriptorSetCount = static_cast<uint32_t>(DESC_COUNT);
    ALLOC_INFO.pSetLayouts = LAYOUTS.data();

    DESCRIPTOR_SETS.resize(DESC_COUNT);

    if (vkAllocateDescriptorSets(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &ALLOC_INFO, this->DESCRIPTOR_SETS.data()) != VK_SUCCESS) {
        DEBUG_ERR("Failed to create Descriptor sets !");
        throw std::runtime_error("failed to allocate descriptor sets!");
    }
    DEBUG_LOG("SUCCESSFULLY created Descriptor sets");
}

void VULKAN_DESC_SET::UPDATE_SETS(RE2_UBO_OBJ& UBO)
{
    for(uint32_t i = 0; i < this->DESC_COUNT; ++i)
    {
        VkDescriptorBufferInfo BUFFER_INFO{};
        BUFFER_INFO.buffer = UBO.BUFFER[i];
        BUFFER_INFO.offset = 0;
        BUFFER_INFO.range = sizeof(RE2_UBO);

        VkWriteDescriptorSet DESCRIPTOR_WRITE{};
        DESCRIPTOR_WRITE.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        DESCRIPTOR_WRITE.dstSet = this->DESCRIPTOR_SETS[i];
        DESCRIPTOR_WRITE.dstBinding = 0;
        DESCRIPTOR_WRITE.dstArrayElement = 0;
        DESCRIPTOR_WRITE.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        DESCRIPTOR_WRITE.descriptorCount = 1;
        DESCRIPTOR_WRITE.pBufferInfo = &BUFFER_INFO;
        DESCRIPTOR_WRITE.pImageInfo = nullptr; // Optional
        DESCRIPTOR_WRITE.pTexelBufferView = nullptr; // Optional
        vkUpdateDescriptorSets(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), 1, &DESCRIPTOR_WRITE, 0, nullptr);
    }
}

void VULKAN_DESC_SET::FREE()
{
    vkDestroyDescriptorPool(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->DESCRIPTOR_POOL, nullptr);
    vkDestroyDescriptorSetLayout(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->DESCRIPTOR_SET_LAYOUT, nullptr);
}
