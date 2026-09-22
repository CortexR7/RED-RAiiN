#include <RE2_UNIFORM_BUFFER_OBJECT.hpp>
#include <chrono>
#include <cstdint>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


void RE2_UBO_OBJ::INIT(VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, const VkCommandPool& CMD_POOL, uint8_t UBO_COUNT)
{
    this->UBO_COUNT = UBO_COUNT;
    RE2_VK_BUFFER::INIT(LGD, PHD, CMD_POOL, UBO_COUNT);
    this->DATA_PTRs.resize(UBO_COUNT);
    this->UBOs.resize(UBO_COUNT);

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

void RE2_UBO_OBJ::UPDATE_UBO(uint32_t INDEX, VULKAN_SWAPCHAIN& SW)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    RE2_UBO UBO{};
    UBO.MODEL = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    UBO.VIEW = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    UBO.PROJECTION = glm::perspective(glm::radians(45.0f), SW.GET_SWAPCHAIN_RESOLUTION().width / (float) SW.GET_SWAPCHAIN_RESOLUTION().height, 0.1f, 10.0f);
    UBO.PROJECTION[1][1] *= -1;

    memcpy(this->DATA_PTRs[INDEX], &UBO, sizeof(UBO));
    this->UBOs[INDEX] = UBO;
}

void RE2_UBO_OBJ::FREE()
{
    RE2_VK_BUFFER::FREE();
}
