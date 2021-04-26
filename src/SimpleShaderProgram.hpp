#pragma once
#include "ShaderProgram.hpp"

#include <utility>

class SimpleShaderProgram: public ShaderProgram {
public:
    SimpleShaderProgram();
    ~SimpleShaderProgram();

    void setupVertexAttributePointers();
    bool getUniformLocation(std::string uniformName, unsigned int &loc);
private:
    std::pair<std::string, unsigned int>* m_uniformBindings;
    unsigned int m_nrOfUniforms;
};
