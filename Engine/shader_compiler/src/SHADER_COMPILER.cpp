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

void SLANG2SPIRV::createComposedProgram()
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
    std::cout << ">>> createModuleVertex\n" << std::flush;
    createModuleVertex();
    std::cout << ">>> createEntryPointsVertex\n" << std::flush;
    createEntryPointsVertex();
    std::cout << ">>> createComposedProgram\n" << std::flush;
    createComposedProgram();
    std::cout << ">>> linkVertexProgram\n" << std::flush;
    linkVertexProgram();
    std::cout << ">>> compileVertexShader\n" << std::flush;
    compileVertexShader();
    std::cout << ">>> DONE\n" << std::flush;
}

std::vector<char> SLANG2SPIRV::GET_SHADER_CODE_AS_CHAR_VECTOR()
{
    return VERTEX_SPIRV_CODE;
}