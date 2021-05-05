#pragma once

#include "Camera.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"
#include "Objects/Quad.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

    void draw();
private:
    Camera m_camera;
    SimpleShaderProgram m_shaderProgram;
    Quad m_quad;

    void initGL();
};
