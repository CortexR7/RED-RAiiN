#ifndef RE2_INDEX_BUFFER_H
#define RE2_INDEX_BUFFER_H


#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <cstdint>
#include <vulkan/vulkan.h>
#include <RE2_VK_BUFFER.hpp>


class RE2_INDEX_BUFFER : public RE2_VK_BUFFER{

    public:
    std::vector<VkBuffer> BUFFER;
    std::vector<VkDeviceMemory> BUFFER_MEMORY;
    std::vector<uint16_t> INDEX_COUNT;

    void INIT(
        void* DATA,
        size_t SIZE,
        VULKAN_LOGICAL_DEVICE LGD,
        VULKAN_PHYSICAL_DEVICE PHD,
        const VkCommandPool& CMD_POOL
    ) override;

    void INIT(
        void* DATA,
        size_t SIZE,
        VULKAN_LOGICAL_DEVICE LGD,
        VULKAN_PHYSICAL_DEVICE PHD,
        const VkCommandPool& CMD_POOL,
        uint16_t INDEX_COUNT
    );

    void COPY_BUFFER_DATA(
        VkBuffer SRC_BUFFER,
        VkBuffer DST_BUFFER,
        VkDeviceSize SIZE
    );

    size_t EXPOSE_SIZE(uint32_t n);

    void FREE();
};

#endif
