#ifndef SHADER_COMPILER
#define SHADER_COMPILER

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


    public:
    void createSoloSession();
    
    void createModuleVertex();
    void createEntryPointsVertex();
    void createComposedProgram();
    void linkVertexProgram();
    void compileVertexShader();
    void GEN_VERTEX_SHADER();



    std::vector<char> GET_SHADER_CODE_AS_CHAR_VECTOR();

    SLANG2SPIRV();
    ~SLANG2SPIRV();
};


#endif