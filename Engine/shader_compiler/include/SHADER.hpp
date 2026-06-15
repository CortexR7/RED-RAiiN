#ifndef SHADER_HPP
#define SHADER_HPP
#include <vector>

enum SHADER_TYPE{
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    TESSELLATION_SHADER,
    GEOMETRY_SHADER,
    COMPUTE_SHADER,
    NO_SHADER
};

class SHADER{
    public:
    SHADER();

    std::vector<char> SPIRV_SHADER_CODE;
    SHADER_TYPE SHADER_TYPE;
};

#endif