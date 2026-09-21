#include <vulkan/vulkan.h>
#include <VULKAN_DESC_SET.hpp>

#define DEBUG_ON
#include <ETL.hpp>

void VULKAN_DESC_SET::INIT(VULKAN_LOGICAL_DEVICE LGD)
{
    this->INTERNAL_LGD = LGD;
    VkDescriptorSetLayoutBinding UBO_LAYOUT_BINDING{};
    UBO_LAYOUT_BINDING.binding = 0;
    UBO_LAYOUT_BINDING.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    UBO_LAYOUT_BINDING.descriptorCount = 0;
    UBO_LAYOUT_BINDING.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    UBO_LAYOUT_BINDING.pImmutableSamplers = nullptr;


    VkDescriptorSetLayoutCreateInfo LAYOUT_INFO{};
    LAYOUT_INFO.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;;
    LAYOUT_INFO.bindingCount = 1;
    LAYOUT_INFO.pBindings = &UBO_LAYOUT_BINDING;

    if(vkCreateDescriptorSetLayout(LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &LAYOUT_INFO, nullptr, &this->DESCRIPTOR_SET_LAYOUT) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
    DEBUG_LOG("Created Descriptor set layout for UBO");
}

void VULKAN_DESC_SET::FREE()
{
    vkDestroyDescriptorSetLayout(this->INTERNAL_LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), this->DESCRIPTOR_SET_LAYOUT, nullptr);
}
