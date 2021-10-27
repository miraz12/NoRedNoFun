#pragma once
#include "ShaderProgram.hpp"

class SimpleShaderProgram: public ShaderProgram {
public:
    SimpleShaderProgram();
    ~SimpleShaderProgram();

    void setupVertexAttributePointers() override;
};
