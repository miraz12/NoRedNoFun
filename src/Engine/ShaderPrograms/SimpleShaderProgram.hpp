#pragma once
#include "ShaderProgram.hpp"

#include <utility>
#include <unordered_map>

class SimpleShaderProgram: public ShaderProgram {
public:
    SimpleShaderProgram();
    ~SimpleShaderProgram();

    void setupVertexAttributePointers();
    unsigned int getUniformLocation(std::string uniformName);
private:
    std::unordered_map<std::string, unsigned int> m_uniformBindings;
};
