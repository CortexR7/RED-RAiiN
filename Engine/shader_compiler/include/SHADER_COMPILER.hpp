#ifndef SHADER_COMPILER_HPP
#define SHADER_COMPILER_HPP

#include <vulkan/vulkan.h>
#include <slang/slang.h>
#include <slang/slang-com-ptr.h>
#include <slang/slang-com-helper.h>
#include <vector>

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