#ifndef RENDER_ENGINE_2_HPP
#define RENDER_ENGINE_2_HPP

#include <WINDOW.hpp>
#include <VULKAN_INSTANCE.hpp>


/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the render_engine itself and all its core functionalities
*  the engine is still in alpha stage and is under heavy development.
*  In future the vulkanaid module will probably get merged with the render engine.
*  The render engine uses now a half baked approach where it uses vulkanaid as a vulkan abstraction
*  to create some of the setup while other functionality is getting implemented by the engine itself.
*  This is not ideal and will be changed later.
*  For now I dont know in which direction it will go but it will either remove vulkanaid fully or shift all the logic to vulkanaid over.
*/

class RENDER_ENGINE2{
    private:

    public:
    WINDOW MAIN_WINDOW;
    VULKAN_INSTANCE VK_INSTANCE;
    

    void INIT_ENGINE();
    void RUN_ENGINE();
};

#endif