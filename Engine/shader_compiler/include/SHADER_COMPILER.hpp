#ifndef SHADER_COMPILER
#define SHADER_COMPILER

#include <vulkan/vulkan.h>
#include <slang/slang.h>
#include <slang/slang-com-ptr.h>
#include <slang/slang-com-helper.h>

class SLANG2SPIRV{
    private:
    Slang::ComPtr<slang::IGlobalSession> globalSession;

    public:
    void createSoloSession();

    SLANG2SPIRV();
    ~SLANG2SPIRV();
};


#endif