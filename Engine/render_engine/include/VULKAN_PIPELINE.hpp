#ifndef VULKAN_PIPELINE_HPP
#define VULKAN_PIPELINE_HPP

#include <vulkan/vulkan.h>
#include <VULKAN_LOGICAL_DEVICE.hpp>
#include <VULKAN_SWAPCHAIN.hpp>
#include <SHADER_LIB.hpp>

#define DEBUG_ON            // NOTE: comment this line out to disable debug logs for "VULKAN_PIPELINE.cpp"
#include <ETL.hpp>

/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the GPU Pipeline class which will
*  handle the creation of the Pipeline and hold the ressources relative too it such as the shaders.
*/


class VULKAN_PIPELINE{
    private:
    ETL::StaticArray<SHADER> SHADERS{2};
    VkPipelineLayout PIPELINE_LAYOUT;

    void INIT_PIPELINE_LAYOUT(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE, VULKAN_SWAPCHAIN& SWAPCHAIN, VkShaderModule& vertexShaderModule, VkShaderModule& fragmentShaderModule);
    void INIT_GRAPHICS_PIPELINE();


    public:
    void INIT(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE, VULKAN_SWAPCHAIN& SWAPCHAIN);
    void FREE(VULKAN_LOGICAL_DEVICE& LOGICAL_DEVICE);
};

#endif