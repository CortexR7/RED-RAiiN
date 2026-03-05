#include <SHADER_COMPILER.hpp>


SLANG2SPIRV::SLANG2SPIRV()
{
    createGlobalSession(this->globalSession.writeRef());
}
SLANG2SPIRV::~SLANG2SPIRV(){}


void SLANG2SPIRV::createSoloSession()
{
    slang::SessionDesc sessionDesc = {};

    slang::TargetDesc targetDesc = {};
    targetDesc.format = SLANG_SPIRV;
    targetDesc.profile = this->globalSession->findProfile("spirv_1_3");

    sessionDesc.targets = &targetDesc;
    sessionDesc.targetCount = 1;

    // skip macros for now
    sessionDesc.preprocessorMacros = nullptr;
    sessionDesc.preprocessorMacroCount = 0;

    
}