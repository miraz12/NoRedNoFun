#pragma once

#include "Camera.hpp"
#include "Objects/Quad.hpp"
#include "MapLoader/MapLoader.hpp"
#include "ShaderPrograms/SimpleShaderProgram.hpp"
#include "ShaderPrograms/InstancedShaderProgram.hpp"
#include "ShaderPrograms/QuadShaderProgram.hpp"
#include "ShaderPrograms/Effects/CrtEffect.hpp"
#include "Objects/ScreenQuad.hpp"
#include "Objects/InstancedQuadManager.hpp"
#include "Objects/LowPolyLiquid.hpp"
#include "Objects/BlurObject.hpp"

#include <array>

class Rendering {
public:
    static Rendering& getInstance() {
        static Rendering instance; 
		return instance;
    }

    Rendering(Rendering const&) = delete;
	void operator=(Rendering const&) = delete;

    ~Rendering() = default;

    void reset();
	Quad* getNewQuad();
    InstancedQuadManager* getQuadManager();
	Camera* getCamera();
    MapLoader* getMapLoader();

    
	void update(float dt);
    void draw();
    void init(unsigned int width, unsigned int height);
    void reInit(unsigned int width, unsigned int height);
private:
    Rendering();

    Camera m_camera;

    InstancedShaderProgram m_instancedShaderProgram;
    InstancedQuadManager m_quadManager;

    SimpleShaderProgram m_simpleShaderProgram;
    LowPolyLiquid m_lowPolyLiquid;

    QuadShaderProgram m_screenShaderProgram;
    ScreenQuad m_screenQuad;

    CrtEffect m_crtEffect;
    ScreenQuad m_quadCrt;
    MapLoader m_mapLoader;

    // Framebuffer variables
    std::array<unsigned int, 2> m_fbos;
    std::array<unsigned int, 2> m_colTexs;
    std::array<unsigned int, 2> m_rbos;

    unsigned int m_width, m_height;
    unsigned int quadVAO, quadVBO;
    void initGL();
};
