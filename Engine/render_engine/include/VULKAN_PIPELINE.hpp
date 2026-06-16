#ifndef VULKAN_PIPELINE_HPP
#define VULKAN_PIPELINE_HPP

#include <vulkan/vulkan.h>
#include <SHADER_LIB.hpp>

#define DEBUG_ON
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
    
    public:
};

#endif