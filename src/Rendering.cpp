#include "Rendering.hpp"

#include <iostream>
#include <glad/glad.h>
#include <time.h>

Rendering::Rendering():
	m_quadManager(m_instancedShaderProgram),
	m_lowPolyLiquid(m_simpleShaderProgram),
    m_mapLoader(m_simpleShaderProgram),
	m_opacity(255.0f) {
    initGL();
    m_camera.setPosition(0.0f, 0.0f);
    m_camera.setZoom(1.0f);
    m_camera.setRotation(0.0f);

    Quad* tempQuad = m_quadManager.getNewQuad(); // Add quad

    std::srand(std::time(NULL));
    for (unsigned int i = 0; i < 100; i++) {
        m_lowPolyLiquid.addStop(glm::vec3(std::rand() % 100 * 0.01f - 0.5f, std::rand() % 100 * 0.01f - 0.5f, 0.0f));
    }
}

Rendering::~Rendering() {

}

void Rendering::update(float dt) {
    m_opacity -= 150.0f * dt;
    if (m_opacity < 0) {
        m_opacity = 255.0f;
    }
    m_pixelData[3] = (unsigned char) std::floor(m_opacity);
    m_quadManager.getTexture().updateTextureSubData(m_pixelData, 0, 0, 1, 1);
}

void Rendering::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_camera.bindViewMatrix(m_instancedShaderProgram.getUniformLocation("viewMatrix"));
    m_instancedShaderProgram.use();
	m_quadManager.draw();
    m_simpleShaderProgram.use();
    m_lowPolyLiquid.draw();
    //m_mapLoader.draw();
}

void Rendering::initGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

//     glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // Back-face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

//     glEnable(GL_LINE_SMOOTH); // Line antialiasing
    glLineWidth(3.0f); // Sets line width of things like wireframe and draw lines
    glPointSize(3.0f);
}
