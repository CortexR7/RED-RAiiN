#include <render_engine.hpp>
#include <RENDER_ENGINE2.hpp>
#include <tools.hpp>
#include <iostream>
#include <SHADER_COMPILER.hpp>


int main(){
    LOG("Starting HATE Render Engine...");

    
    RenderEngine renderEngine;
    renderEngine.run();

    if(vulkanaid::DEBUG_MODE){
        std::cin.get();
    }
    

    /*
    RENDER_ENGINE2 RENDER_ENGINE;
    RENDER_ENGINE.RUN_ENGINE();
    SLANG2SPIRV shaderCompiler;
    shaderCompiler.createSoloSession();
    */
 
    return 0;
}