#include <SHADER_COMPILER.hpp>
#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include <cstring>


SLANG2SPIRV::SLANG2SPIRV()
{
    createGlobalSession(this->globalSession.writeRef());
    this->createSoloSession();
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
                {slang::CompilerOptionValueKind::Int, SLANG_OPTIMIZATION_LEVEL_HIGH, 0, nullptr, nullptr}
            }
        }
    };

    sessionDesc.compilerOptionEntries = compilerOptions.data();
    sessionDesc.compilerOptionEntryCount = compilerOptions.size();

    this->globalSession->createSession(sessionDesc, this->session.writeRef());
}

static std::string loadShaderFromFilePathAsString(std::string path)
{
	std::string err = "ERROR LOOK AT LOGS";

	try {
		std::ifstream streamFromPath;
		streamFromPath.open(path.c_str());

		std::stringstream stream;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		stream << streamFromPath.rdbuf();
		streamFromPath.close();
		return stream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR WHILE TRYING TO READ THE SHADER FROM PATH\n";
		std::cout << "COULD NOT CONVERT PATH INTO STREAM\n\n\n";
        std::cout << e.what() << "\n";
	}

	return err;
}

void SLANG2SPIRV::createModuleVertex()
{
    Slang::ComPtr<slang::IBlob> diagnosticBlob;
    const char* moduleName = "vertex";
    const char* modulePath = "vertex_shader.slang";
    this->vertex_shader_source = loadShaderFromFilePathAsString("vertex_shader.slang");

    this->slangModuleVertex = this->session->loadModuleFromSourceString(moduleName, modulePath, vertex_shader_source.c_str(), diagnosticBlob.writeRef());
    if(!this->slangModuleVertex)
    {
        std::runtime_error("FAILED TO COMPILE MINIMAL SHADERS !");
    }
}

void SLANG2SPIRV::createEntryPointsVertex()
{
    Slang::ComPtr<slang::IBlob> diagnosticsBlob;
    this->slangModuleVertex->findEntryPointByName("main", this->entryPointVertex.writeRef());

    if (!this->entryPointVertex)
    {
        std::runtime_error("FAILED TO FETCH ENTRY POINT FROM THE VERTEX SHADER !");
    }
}

void SLANG2SPIRV::createComposedProgramVertex()
{
    std::array<slang::IComponentType*, 2> componentTypes = 
    {
        this->slangModuleVertex,
        this->entryPointVertex
    };

    SlangResult result = this->session->createCompositeComponentType(
        componentTypes.data(),
        componentTypes.size(),
        composedVertexProgram.writeRef(),
        nullptr                 // leaving the blob out for now 
    );
}

void SLANG2SPIRV::linkVertexProgram()
{
    SlangResult result = this->composedVertexProgram->link(
        this->linkedVertexProgram.writeRef(),
        nullptr                 // leaving the blob out for now 
    );
}

static std::vector<char> turnBlobIntoVector(Slang::ComPtr<slang::IBlob>& blob)
{
    std::vector<char> data(static_cast<size_t>(blob->getBufferSize()));
    std::memcpy(data.data(), blob->getBufferPointer(), static_cast<size_t>(blob->getBufferSize()));
    return data;
}

void SLANG2SPIRV::compileVertexShader()
{
    SlangResult result = this->linkedVertexProgram->getTargetCode(
        0,
        this->spirvCodeVertex.writeRef(),
        nullptr
    );
    this->VERTEX_SPIRV_CODE = turnBlobIntoVector(this->spirvCodeVertex);
}

void SLANG2SPIRV::GEN_VERTEX_SHADER()
{
    DEBUG_LOG(">>> createModuleVertex");
    createModuleVertex();
    DEBUG_LOG(">>> createEntryPointsVertex");
    createEntryPointsVertex();
    DEBUG_LOG(">>> createComposedProgram");
    createComposedProgramVertex();
    DEBUG_LOG(">>> linkVertexProgram");
    linkVertexProgram();
    DEBUG_LOG(">>> compileVertexShader");
    compileVertexShader();
    DEBUG_LOG(">>> DONE");
}

std::vector<char> SLANG2SPIRV::GET_SHADER_CODE_AS_CHAR_VECTOR_VERTEX()
{
    return VERTEX_SPIRV_CODE;
}



void SLANG2SPIRV::createModuleFragment()
{
    Slang::ComPtr<slang::IBlob> diagnosticBlob;
    const char* moduleName = "fragment";
    const char* modulePath = "fragment_shader.slang";
    this->fragment_shader_source = loadShaderFromFilePathAsString("fragment_shader.slang");

    this->slangModuleFragment = this->session->loadModuleFromSourceString(moduleName, modulePath, fragment_shader_source.c_str(), diagnosticBlob.writeRef());
    if(!this->slangModuleFragment)
    {
        std::runtime_error("FAILED TO COMPILE MINIMAL SHADERS !");
    }
}

void SLANG2SPIRV::createEntryPointsFragment()
{
    Slang::ComPtr<slang::IBlob> diagnosticsBlob;
    this->slangModuleFragment->findEntryPointByName("main", this->entryPointFragment.writeRef());

    if (!this->entryPointFragment)
    {
        std::runtime_error("FAILED TO FETCH ENTRY POINT FROM THE VERTEX SHADER !");
    }
}

void SLANG2SPIRV::createComposedProgramFragment()
{
    std::array<slang::IComponentType*, 2> componentTypes = 
    {
        this->slangModuleFragment,
        this->entryPointFragment
    };

    SlangResult result = this->session->createCompositeComponentType(
        componentTypes.data(),
        componentTypes.size(),
        composedFragmentProgram.writeRef(),
        nullptr                 // leaving the blob out for now 
    );
}

void SLANG2SPIRV::linkFragmentProgram()
{
    SlangResult result = this->composedFragmentProgram->link(
        this->linkedFragmentProgram.writeRef(),
        nullptr                 // leaving the blob out for now 
    );
}

void SLANG2SPIRV::compileFragmentShader()
{
    SlangResult result = this->linkedFragmentProgram->getTargetCode(
        0,
        this->spirvCodeFragment.writeRef(),
        nullptr
    );
    this->FRAGMENT_SPIRV_CODE = turnBlobIntoVector(this->spirvCodeFragment);
}

void SLANG2SPIRV::GEN_FRAGMENT_SHADER()
{
    createModuleFragment();
    DEBUG_LOG(">>> createModuleFrag");
    createEntryPointsFragment();
    DEBUG_LOG(">>> createEntryPointsFrag");
    createComposedProgramFragment();
    DEBUG_LOG(">>> link frag");
    linkFragmentProgram();
    DEBUG_LOG(">>> compile frag");
    compileFragmentShader();
    DEBUG_LOG(">>> DONE");
}

std::vector<char> SLANG2SPIRV::GET_SHADER_CODE_AS_CHAR_VECTOR_FRAGMENT()
{
    return FRAGMENT_SPIRV_CODE;
}