#include <VULKAN_SYNC.hpp>


void VULKAN_SYNC::INIT(VULKAN_LOGICAL_DEVICE& DEVICE, uint8_t FRAMES_IN_FLIGHT, VULKAN_SWAPCHAIN& SW)
{
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    this->SEMAPHORES_RENDER_FINISHED_PER_SW.RE_SIZE(FRAMES_IN_FLIGHT);
    this->SEMAPHORES_RENDER_FINISHED.RE_SIZE(FRAMES_IN_FLIGHT);
    this->SEMAPHORES_IMAGE_AVAILABLE.RE_SIZE(FRAMES_IN_FLIGHT);
    this->FENCES.RE_SIZE(FRAMES_IN_FLIGHT);

    for(auto& SEMAPHORE : SEMAPHORES_RENDER_FINISHED_PER_SW)
    {
        SEMAPHORE.SEMAPHORES.RE_SIZE(SW.SW_IMAGE_COUNT);
        for(size_t i = 0; i < SEMAPHORE.SEMAPHORES.SIZE(); ++i)
        {
            if(vkCreateSemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &semaphoreInfo, nullptr, &SEMAPHORE.SEMAPHORES.DATA()[i]) != VK_SUCCESS){
                DEBUG_LOG("SEMAPHORE CREATION FAILES !");
            } else {
                DEBUG_LOG("SEMAPHORE CREATED SUCCES !");
            }
        }
    }

    for(auto& SEMAPHORE : SEMAPHORES_RENDER_FINISHED)
    {
        if(vkCreateSemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &semaphoreInfo, nullptr, &SEMAPHORE) != VK_SUCCESS){
            DEBUG_LOG("SEMAPHORE CREATION FAILES !");
        } else {
            DEBUG_LOG("SEMAPHORE CREATED SUCCES !");
        }
    }

    for(auto& SEMAPHORE : SEMAPHORES_IMAGE_AVAILABLE)
    {
        if(vkCreateSemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &semaphoreInfo, nullptr, &SEMAPHORE) != VK_SUCCESS){
            DEBUG_LOG("SEMAPHORE CREATION FAILES !");
        } else {
            DEBUG_LOG("SEMAPHORE CREATED SUCCES !");
        }
    }

    
    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for(auto& FENCE : FENCES)
    {
        if(vkCreateFence(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &fenceInfo, nullptr, &FENCE) != VK_SUCCESS){
            DEBUG_LOG("FAILED TO MAKE FENCE");
        } else {
            DEBUG_LOG("FENCES CREATED SUCCESFULLY");
        }
    }
}

void VULKAN_SYNC::FREE(VULKAN_LOGICAL_DEVICE& DEVICE)
{
    for(auto& FENCE : this->FENCES)
    {
        vkDestroyFence(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(),  FENCE, nullptr);
    }

    for(auto& SEMAPHORE : this->SEMAPHORES_RENDER_FINISHED_PER_SW)
    {
        for(size_t i = 0; i < SEMAPHORE.SEMAPHORES.SIZE(); ++i)
        {
            vkDestroySemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), SEMAPHORE.SEMAPHORES.DATA()[i], nullptr);
        }
    }

    for(auto& SEMAPHORE : this->SEMAPHORES_IMAGE_AVAILABLE)
    {
        vkDestroySemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), SEMAPHORE, nullptr);
    }

    for(auto& SEMAPHORE : this->SEMAPHORES_RENDER_FINISHED)
    {
        vkDestroySemaphore(DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), SEMAPHORE, nullptr);
    }
}