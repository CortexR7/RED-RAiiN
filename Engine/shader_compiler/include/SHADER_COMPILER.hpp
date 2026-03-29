#ifndef SHADER_COMPILER_HPP
#define SHADER_COMPILER_HPP

#define SLANG_STATIC
#include <vulkan/vulkan.h>
#include <slang/slang.h>
#include <slang/slang-com-ptr.h>
#include <slang/slang-com-helper.h>
#include <vector>
#include <string>


/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the SLANG2SPIRV shader compiler.
*  This shader compiler is still in heavy development.
*  There are a lot of hardcoded values especially for the file pathes etc.
*  
*  Future versions of this shader compiler should implement a more dynamic appraoch
*  for handling shader compilation.
*  
*
*  Certain approaches can look like this:
*
*  - remove the hardcoded file paths
*  - remove the identity added to the modules (currently it uses clear identeties but the compiled modules really are not tied to that)
*  - dont use member variables for all different types of shaders as it will polute the object with "shaader storage variables".
*    This object is supposed to only model the functionality of a shader compiler and not model a data/storage object.
* 
*/



class SLANG2SPIRV{
    private:
    Slang::ComPtr<slang::IGlobalSession> globalSession;
    Slang::ComPtr<slang::ISession> session;

    std::string vertex_shader_source;
    Slang::ComPtr<slang::IModule> slangModuleVertex;
    Slang::ComPtr<slang::IEntryPoint> entryPointVertex;
    Slang::ComPtr<slang::IComponentType> composedVertexProgram;
    Slang::ComPtr<slang::IComponentType> linkedVertexProgram;
    Slang::ComPtr<slang::IBlob> spirvCodeVertex;
    std::vector<char> VERTEX_SPIRV_CODE;

    std::string fragment_shader_source;
    Slang::ComPtr<slang::IModule> slangModuleFragment;
    Slang::ComPtr<slang::IEntryPoint> entryPointFragment;
    Slang::ComPtr<slang::IComponentType> composedFragmentProgram;
    Slang::ComPtr<slang::IComponentType> linkedFragmentProgram;
    Slang::ComPtr<slang::IBlob> spirvCodeFragment;
    std::vector<char> FRAGMENT_SPIRV_CODE;


    public:
    void createSoloSession();
    
    void createModuleVertex();
    void createEntryPointsVertex();
    void createComposedProgramVertex();
    void linkVertexProgram();
    void compileVertexShader();
    void GEN_VERTEX_SHADER();


    void createModuleFragment();
    void createEntryPointsFragment();
    void createComposedProgramFragment();
    void linkFragmentProgram();
    void compileFragmentShader();
    void GEN_FRAGMENT_SHADER();



    std::vector<char> GET_SHADER_CODE_AS_CHAR_VECTOR_VERTEX();
    std::vector<char> GET_SHADER_CODE_AS_CHAR_VECTOR_FRAGMENT();

    SLANG2SPIRV();
    ~SLANG2SPIRV();
};

#endif