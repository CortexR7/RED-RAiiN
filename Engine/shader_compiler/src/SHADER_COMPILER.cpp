#include <SHADER_COMPILER.hpp>
#include <array>

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


    std::array<slang::CompilerOptionEntry, 2> compilerOptions = 
    {
        {
            {
                slang::CompilerOptionName::EmitSpirvDirectly,
                {slang::CompilerOptionValueKind::Int, 1, 0, nullptr, nullptr}
            },

            {
                slang::CompilerOptionName::Optimization,
                {slang::CompilerOptionValueKind::Int, SLANG_OPTIMIZATION_LEVEL_MAXIMAL, 0, nullptr, nullptr}
            }
        }
    };

    sessionDesc.compilerOptionEntries = compilerOptions.data();
    sessionDesc.compilerOptionEntryCount = compilerOptions.size();

    this->globalSession->createSession(sessionDesc, this->session.writeRef());
}
