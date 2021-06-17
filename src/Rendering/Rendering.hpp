#pragma once

#include "Camera.hpp"
#include "Objects/Quad.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"
#include "ShaderPrograms/InstancedShaderProgram.hpp"
#include "Objects/InstancedQuadManager.hpp"
#include "Objects/LowPolyLiquid.hpp"
#include "MapLoader/MapLoader.hpp"

class Rendering {
public:
    Rendering();
    ~Rendering();

	Quad* getNewQuad();

	void update(float dt);
    void draw();
private:
    Camera m_camera;

    InstancedShaderProgram m_instancedShaderProgram;
    InstancedQuadManager m_quadManager;

    SimpleShaderProgram m_simpleShaderProgram;
    LowPolyLiquid m_lowPolyLiquid;
    MapLoader m_mapLoader;

    void initGL();
};
