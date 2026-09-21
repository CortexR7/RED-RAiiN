#ifndef UNIFORM_BUFFER_OBJECT_HPP
#define UNIFORM_BUFFER_OBJECT_HPP

#include <VULKAN_SWAPCHAIN.hpp>
#include <VULKAN_CMD.hpp>
#include <cstdint>
#include <vector>
#include <vulkan/vulkan.h>
#include <RE2_VK_BUFFER.hpp>
#include <glm/glm.hpp>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_PHYSICAL_DEVICE.hpp>


struct RE2_UNIFORM_BUFFER_OBJECT{
    glm::mat4 MODEL;
    glm::mat4 VIEW;
    glm::mat4 PROJECTION;
};
using RE2_UBO = RE2_UNIFORM_BUFFER_OBJECT;


class RE2_UBO_OBJ : RE2_VK_BUFFER{
    private:
        uint8_t UBO_COUNT;
        std::vector<void*> DATA_PTRs;
        std::vector<RE2_UBO> UBOs;

    public:
        void INIT(VULKAN_LOGICAL_DEVICE LGD, VULKAN_PHYSICAL_DEVICE PHD, const VULKAN_CMD& CMD_POOL, uint8_t UBO_COUNT);
        void FREE();

        void UPDATE_UBO(uint32_t INDEX, VULKAN_SWAPCHAIN& SW);
};

#endif
