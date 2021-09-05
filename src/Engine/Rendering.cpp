#include "Rendering.hpp"

#include <iostream>
#include <glad/glad.h>
#include <time.h>

Rendering::Rendering():
	m_quadManager(m_instancedShaderProgram),
	m_lowPolyLiquid(m_simpleShaderProgram),
    m_mapLoader(m_simpleShaderProgram, "resources/Maps/simple.map") {
    initGL();

}

Quad* Rendering::getNewQuad() {
	return m_quadManager.getNewQuad();
}

InstancedQuadManager* Rendering::getQuadManager() {
    return &m_quadManager;
}

Camera* Rendering::getCamera() {
	return &m_camera;
}

MapLoader* Rendering::getMapLoader() {
    return &m_mapLoader;
}

void Rendering::update(float /*dt*/) {
	// Updates to texture matrices for animations etc goes here for example
}

void Rendering::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_simpleShaderProgram.use();
	m_camera.bindViewMatrix(m_simpleShaderProgram.getUniformLocation("viewMatrix"));
    m_mapLoader.draw();
    m_instancedShaderProgram.use();
	m_camera.bindViewMatrix(m_instancedShaderProgram.getUniformLocation("viewMatrix"));
	m_quadManager.draw();
}

void Rendering::initGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // Back-face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

//     glEnable(GL_LINE_SMOOTH); // Line antialiasing
    glLineWidth(3.0f); // Sets line width of things like wireframe and draw lines
    glPointSize(3.0f);
}
