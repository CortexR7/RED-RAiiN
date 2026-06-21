#include <RENDER_ENGINE2.hpp>


void RENDER_ENGINE2::INIT_ENGINE()
{
    VK_INSTANCE.INIT_INSTANCE();
    DEBUG_LOG("Vulkan instance created successfully!");
    MAIN_WINDOW.INIT_WINDOW(this->VK_INSTANCE);
    DEBUG_LOG("Main window initialized!");
    VKP_DEVICE.INIT_DEVICE(this->MAIN_WINDOW, this->VK_INSTANCE);
    DEBUG_LOG("Vulkan physical device initialized!");
    VKL_DEVICE.INIT(this->VKP_DEVICE, MAIN_WINDOW, this->deviceExtensions, this->validationLayers, false); // ! WARNING ! need to figure out why thE "false" is wrong later 
    DEBUG_LOG("Vulkan logical device initialized!");
    VK_SWAPCHAIN.INIT(MAIN_WINDOW, VKP_DEVICE, VKL_DEVICE);
    DEBUG_LOG("Vulkan swapchain initialized!");
    VK_PIPELINE.INIT(VKL_DEVICE, VK_SWAPCHAIN);
    DEBUG_LOG("Vulkan pipeline initialized!");
    VK_CMD.INIT(VKP_DEVICE, MAIN_WINDOW, VKL_DEVICE);
    DEBUG_LOG("Vulkan command pool and buffers initialized!");
    createSyncObjects();
}

void RENDER_ENGINE2::RUN_ENGINE()
{
    while (!glfwWindowShouldClose(MAIN_WINDOW.getWindow()))
    {
        glfwPollEvents();
        DRAW_FRAME();
    }
}

void RENDER_ENGINE2::createSyncObjects()
{
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
        vkCreateSemaphore(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
        vkCreateFence(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create semaphores or fences!");
    }
}

void RENDER_ENGINE2::DRAW_FRAME(void)
{
    vkWaitForFences(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), 1, &inFlightFence);
    uint32_t imageIndex;
    vkAcquireNextImageKHR(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), VK_SWAPCHAIN.SW_CHAIN, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
    VK_CMD.RECORD_CMD_BUFFER_GRAPHICS(VK_CMD.CMD_BUFFERS_GRAPHICS[0], imageIndex, VK_SWAPCHAIN, VK_PIPELINE);


    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &VK_CMD.CMD_BUFFERS_GRAPHICS[0];

    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(VKL_DEVICE.VK_QUEUE.GRAPHICS_QUEUE, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }


    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {VK_SWAPCHAIN.SW_CHAIN};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(VKL_DEVICE.VK_QUEUE.PRESENT_QUEUE, &presentInfo);
}

void RENDER_ENGINE2::FREE_ENGINE()
{
    vkDeviceWaitIdle(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE());
    vkDestroySemaphore(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), renderFinishedSemaphore, nullptr);
    vkDestroyFence(VKL_DEVICE.GET_HANDLE_TO_VK_LOGICAL_DEVICE(), inFlightFence, nullptr);
    VK_CMD.FREE(VKL_DEVICE);
    VK_PIPELINE.FREE(VKL_DEVICE);
    VK_SWAPCHAIN.FREE();
    MAIN_WINDOW.FREE(VK_INSTANCE);
    VKL_DEVICE.FREE();
    VK_INSTANCE.FREE();
}

RENDER_ENGINE2::RENDER_ENGINE2()
{
    this->INIT_ENGINE();
}

RENDER_ENGINE2::~RENDER_ENGINE2()
{
    this->FREE_ENGINE();
}