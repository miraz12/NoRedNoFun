#pragma once

#include "Camera.hpp"
#include "Objects/Quad.hpp"
#include "MapLoader/MapLoader.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"
#include "ShaderPrograms/InstancedShaderProgram.hpp"
#include "Objects/InstancedQuadManager.hpp"
#include "Objects/LowPolyLiquid.hpp"

class Rendering {
public:
    static Rendering& getInstance() {
        static Rendering instance; 
		return instance;
    }

    Rendering(Rendering const&) = delete;
	void operator=(Rendering const&) = delete;

    ~Rendering() = default;

	Quad* getNewQuad();
    InstancedQuadManager* getQuadManager();
	Camera* getCamera();
    MapLoader* getMapLoader();

	void update(float dt);
    void draw();
private:
    Rendering();

    Camera m_camera;

    InstancedShaderProgram m_instancedShaderProgram;
    InstancedQuadManager m_quadManager;

    SimpleShaderProgram m_simpleShaderProgram;
    LowPolyLiquid m_lowPolyLiquid;

    MapLoader m_mapLoader;
    void initGL();
};
