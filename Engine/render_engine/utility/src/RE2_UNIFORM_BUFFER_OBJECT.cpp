#include <RE2_UNIFORM_BUFFER_OBJECT.hpp>


void RE2_UBO_OBJ::INIT(VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, const VULKAN_CMD& CMD_POOL, uint8_t UBO_COUNT)
{
    this->UBO_COUNT = UBO_COUNT;
    RE2_VK_BUFFER::INIT(LGD, PHD, CMD_POOL.CMD_POOL_GRAPHICS, UBO_COUNT);

    for(int i = 0; i < UBO_COUNT; ++i)
    {
        RE2_VK_BUFFER::CREATE_BUFFER(
            sizeof(RE2_UBO),
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            RE2_VK_BUFFER::BUFFER[i],
            RE2_VK_BUFFER::BUFFER_MEMORY[i]
        );
        vkMapMemory(
            RE2_VK_BUFFER::LGD.GET_HANDLE_TO_VK_LOGICAL_DEVICE(),
            RE2_VK_BUFFER::BUFFER_MEMORY[i],
            0,
            sizeof(RE2_UBO),
            0,
            &this->DATA_PTRs[i]
        );
    }
}
