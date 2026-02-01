#include "vulkan/vulkan_core.h"
#include <render_engine.hpp>


// DUMMY INDICES FOR THE DUMMY VERTICES
const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};

void RenderEngine::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(uint16_t) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        stagingBuffer,
        stagingBufferMemory
    );

    void* data;
    vkMapMemory(this->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(this->device, stagingBufferMemory);

    createBuffer(
        bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        this->indexBuffer,
        this->indexBufferMemory
    );

    copyBuffer(stagingBuffer, this->indexBuffer, bufferSize);

    vkDestroyBuffer(this->device, stagingBuffer, nullptr);
    vkFreeMemory(this->device, stagingBufferMemory, nullptr);
}
