#define LOGGER_ON
#include <render_engine.hpp>
#include <RENDER_ENGINE2.hpp>
#include <tools.hpp>
#include <iostream>
#include <SHADER_COMPILER.hpp>
#include <ETL.hpp>


int main(){
    LOG("Starting RED-RAiiN Engine...");
    
    RENDER_ENGINE2 RENDER_ENGINE;
    RENDER_ENGINE.RUN_ENGINE();
    
    LOG("Exit Game Engine ...");
 
    return 0;
}
