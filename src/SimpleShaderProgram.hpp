#pragma once
#include "ShaderProgram.hpp"

#include <utility>

class SimpleShaderProgram: public ShaderProgram {
public:
    SimpleShaderProgram();
    ~SimpleShaderProgram();

    void setupVertexAttributePointers();
    unsigned int getUniformLocation(std::string uniformName);
private:
    std::pair<std::string, unsigned int>* m_uniformBindings;
    unsigned int m_nrOfUniforms;
};
