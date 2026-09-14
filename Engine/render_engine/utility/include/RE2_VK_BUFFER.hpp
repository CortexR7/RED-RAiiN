#ifndef RE2_VK_BUFFER_H
#define RE2_VK_BUFFER_H

/*
*  Copyright (c) 2026 CortexR7
*
*  This Header file defines a vulkan buffer object.
*  Which can take input data and store it in Memory.
*/


#include <vulkan/vulkan.h>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>

#define DEBUG_ON                    // NOTE: Comment this macro out if u want to disable DEBUG_LOGs for RE2_VK_BUFFER
#include <ETL.hpp>


class RE2_VK_BUFFER{

    private:
    void SETUP_ALLOCATE_MEMORY(         // NOTE: Dont make this method public. This is more a helper for function for
        VULKAN_LOGICAL_DEVICE LGD,      // CREATE_BUFFER so it will also allocate memmory as well.
        VULKAN_PHYSICAL_DEVICE PHD,
        VkBufferUsageFlags USAGE,
        VkDeviceMemory& VERTEX_BUFFER_MEMORY,
        VkBuffer& VERTEX_BUFFER
    );

    public:
    VULKAN_LOGICAL_DEVICE LGD;
    VULKAN_PHYSICAL_DEVICE PHD;
    VkCommandPool CMD_POOL_TRANSFER;

    std::vector<VkDeviceMemory> BUFFER_MEMORY;
    std::vector<VkBuffer> BUFFER;
    std::vector<size_t> BUFFER_SIZE;

    virtual void INIT(void* DATA, size_t SIZE, VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, const VkCommandPool& CMD_POOL);
    void INIT(VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, const VkCommandPool& CMD_POOL);
    void FREE();



    void CREATE_BUFFER(                 // NOTE: creates a Buffer based on USAGE and PROPS
        VkDeviceSize SIZE,
        VkBufferUsageFlags USAGE,
        VkMemoryPropertyFlags PROPS,
        VkBuffer& BUFFER,
        VkDeviceMemory& BUFFER_MEMORY
    );

    void WRITE_BUFFER(
        void* DATA,
        size_t SIZE,
        VkDeviceMemory& BUFFER_MEMORY
    );


    RE2_VK_BUFFER(VULKAN_LOGICAL_DEVICE LGD,VULKAN_PHYSICAL_DEVICE PHD, size_t SIZE, void* DATA, VkCommandPool& CMD_POOL);
    ~RE2_VK_BUFFER();

    RE2_VK_BUFFER();
};

#endif
