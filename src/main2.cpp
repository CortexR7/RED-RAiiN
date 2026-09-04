#define LOGGER_ON
#include <RENDER_ENGINE2.hpp>

#define DEBUG_ON
#include <ETL.hpp>


int main()
{
    DEBUG_LOG("Starting RED-RAiiN Engine...");

    RENDER_ENGINE2 RENDER_ENGINE;
    RENDER_ENGINE.RUN_ENGINE();

    DEBUG_LOG("Exit Game Engine ...");

    return 0;
}
