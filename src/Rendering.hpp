#pragma once

#include "SimpleShaderProgram.hpp"
#include "Quad.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

    void draw();
private:
    SimpleShaderProgram m_shaderProgram;
    Quad m_quad;

    void initGL();
};
