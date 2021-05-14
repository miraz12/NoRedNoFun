#pragma once

#include "Camera.hpp"
#include "Objects/Quad.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"
#include "ShaderPrograms/InstancedShaderProgram.hpp"
#include "Objects/InstancedQuadManager.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

	void update(float dt);
    void draw();
private:
    Camera m_camera;

    InstancedShaderProgram m_shaderProgram;
    InstancedQuadManager m_quadManager;

    void initGL();
};
