#define LOGGER_ON
#include <render_engine.hpp>
#include <RENDER_ENGINE2.hpp>
#include <iostream>
#include <SHADER_COMPILER.hpp>

#define DEBUG_ON
#include <ETL.hpp>


int main(){
    DEBUG_LOG("Starting RED-RAiiN Engine...");
    
    RENDER_ENGINE2 RENDER_ENGINE;
    RENDER_ENGINE.RUN_ENGINE();
    
    DEBUG_LOG("Exit Game Engine ...");
 
    return 0;
}
