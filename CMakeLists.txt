cmake_minimum_required(VERSION 4.4.2)
project("RED-RAiiN")

# defining dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/glfw)


set(SLANG_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_GFX OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_SLANG_RHI OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_REPLAYER OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_DXIL OFF CACHE BOOL "" FORCE)        # skips the DXC/dxil prebuilt download
set(SLANG_ENABLE_CUDA OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_OPTIX OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_NVAPI OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_AFTERMATH OFF CACHE BOOL "" FORCE)
set(SLANG_ENABLE_DOCS OFF CACHE BOOL "" FORCE)        
add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/slang)

set(UPDATE_DEPS ON CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/Vulkan-Loader)


# Bulding local libraries

add_library(ETL INTERFACE)
target_include_directories(
    ETL 
    INTERFACE 
    ${PROJECT_SOURCE_DIR}/Engine/ETL/include
)


add_library(SLANG2SPRIV SHARED)
target_sources(
    SLANG2SPRIV
        PRIVATE
        ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/src/SHADER_COMPILER.cpp
        ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/src/SHADER.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/include
        FILES
        ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/include/SHADER_COMPILER.hpp
        ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/include/SHADER_LIB.hpp
        ${PROJECT_SOURCE_DIR}/Engine/shader_compiler/include/SHADER.hpp
)
target_include_directories(
    SLANG2SPRIV
        PRIVATE
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/external/vulkan/include
)
target_link_libraries(SLANG2SPRIV
    PRIVATE
        ETL
        glfw
        slang
)


add_library(LIBELLE SHARED)
target_sources(
    LIBELLE
        PRIVATE
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/WINDOW.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_SYNC.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_SWAPCHAIN.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_QUEUE.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_PIPELINE.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_PHYSICAL_DEVICE.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_LOGICAL_DEVICE.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_INSTANCE.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/VULKAN_CMD.cpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/src/RENDER_ENGINE2.cpp

        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/Engine/render_engine/include
        FILES
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/GLFW_PREPROCESSOR.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/WINDOW.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_SYNC.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_SWAPCHAIN.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_QUEUE.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_PIPELINE.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_PHYSICAL_DEVICE.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_LOGICAL_DEVICE.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_INSTANCE.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/VULKAN_CMD.hpp
        ${PROJECT_SOURCE_DIR}/Engine/render_engine/include/RENDER_ENGINE2.hpp
)
target_include_directories(
    LIBELLE
        PRIVATE
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/external/vulkan/include
)
target_link_libraries(LIBELLE
    PRIVATE
        ETL
        SLANG2SPRIV
        glfw
        slang
)




# building actual executable

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
    src/main2.cpp
)
target_include_directories(
    ${PROJECT_NAME} 
        PUBLIC
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/include
        ${PROJECT_SOURCE_DIR}/Dependencies/slang/external/vulkan/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE LIBELLE SLANG2SPRIV ETL vulkan)