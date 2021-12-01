#pragma once
#include "System.hpp"
#include "../../Camera.hpp"
#include "../../ShaderPrograms/SimpleShaderProgram.hpp"
#include "../../ShaderPrograms/InstancedShaderProgram.hpp"
#include "../../ShaderPrograms/QuadShaderProgram.hpp"
#include "../../MapLoader/MapLoader.hpp"
#include "../../Objects/InstancedQuadManager.hpp"
#include "../../Objects/ScreenQuad.hpp"

#include <array>


class GraphicsSystem : public System
{
public:

	GraphicsSystem(ECSManager *ECSManager);
	void update(float dt);

	Quad* getNewQuad() { return m_quadManager.getNewQuad(); };
    InstancedQuadManager* getQuadManager() { return &m_quadManager; }
	Camera* getCamera() { return &m_camera; };
    MapLoader* getMapLoader() { return &m_mapLoader; }
    void reset() { m_quadManager.reset(); };

private:
	void draw();
    void initGL();

    Camera m_camera;
    InstancedShaderProgram m_instancedShaderProgram;
    InstancedQuadManager m_quadManager;
    SimpleShaderProgram m_simpleShaderProgram;
    QuadShaderProgram m_screenShaderProgram;
    ScreenQuad m_screenQuad;
    MapLoader m_mapLoader;

    // Framebuffer variables
    std::array<unsigned int, 2> m_fbos;
    std::array<unsigned int, 2> m_colTexs;
    std::array<unsigned int, 2> m_rbos;

    unsigned int m_width, m_height;
    unsigned int quadVAO, quadVBO;
};
