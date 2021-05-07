#pragma once

#include "Camera.hpp"
#include "Objects/Quad.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

	void update(float dt);
    void draw();
private:
    Camera m_camera;
    SimpleShaderProgram m_shaderProgram;

	Quad m_quad;

    void initGL();
};
