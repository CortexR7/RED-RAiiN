#ifndef RE2_VERTEX_BUFFER_H
#define RE2_VERTEX_BUFFER_H


#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>
#include <vulkan/vulkan.h>
#include <RE2_VK_BUFFER.hpp>


class RE2_VERTEX_BUFFER : public RE2_VK_BUFFER{

    public:
    std::vector<VkBuffer> BUFFER;
    std::vector<VkDeviceMemory> BUFFER_MEMORY;

    void INIT(
        void* DATA,
        size_t SIZE,
        VULKAN_LOGICAL_DEVICE LGD,
        VULKAN_PHYSICAL_DEVICE PHD,
        const VkCommandPool& CMD_POOL
    ) override;

    void COPY_BUFFER_DATA(
        VkBuffer SRC_BUFFER,
        VkBuffer DST_BUFFER,
        VkDeviceSize SIZE
    );

    void FREE();
};

#endif
