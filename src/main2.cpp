#include <render_engine.hpp>
#include <RENDER_ENGINE2.hpp>
#include <tools.hpp>
#include <iostream>


int main(){
    LOG("Starting HATE Render Engine...");

    /*
    RenderEngine renderEngine;
    renderEngine.run();

    if(vulkanaid::DEBUG_MODE){
        std::cin.get();
    }
    */

    RENDER_ENGINE2 ENGINE;
    ENGINE.RUN_ENGINE();
 
    return 0;
}