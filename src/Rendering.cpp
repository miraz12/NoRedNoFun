#include "Rendering.hpp"

#include <iostream>
#include <glad/glad.h>

Rendering::Rendering():
	m_quadManager(m_shaderProgram),
	m_opacity(255.0f) {
    initGL();
    m_camera.setPosition(0.0f, 0.0f);
    m_camera.setZoom(1.0f);
    m_camera.setRotation(0.0f);


//     for (unsigned int i = 0; i < 100; i++) {
//         Quad* tempQuad = m_quadManager.getNewQuad(); // Add quad
// 		// Transform it
// 		tempQuad->getModelMatrix() = glm::translate(tempQuad->getModelMatrix(), glm::vec3(-0.9f + 0.2f * (i % 10), -0.9f + 0.2f * std::floor(i / 10), 0.0f));
// 		tempQuad->getModelMatrix() = glm::scale(tempQuad->getModelMatrix(), glm::vec3(0.1f, 0.1f, 1.0f));
//
// 		tempQuad->setNrOfSprites(0.2f * (i % 10), 0.2f * (i / 10));
//     }

    Quad* tempQuad = m_quadManager.getNewQuad(); // Add quad
}

Rendering::~Rendering() {

}

void Rendering::update(float dt) {
    m_opacity -= 150.0f * dt;
    if (m_opacity < 0) {
        m_opacity = 255.0f;
    }
    m_pixelData[3] = std::floor(m_opacity);
    m_quadManager.getTexture().updateTextureSubData(m_pixelData, 0, 0, 1, 1);
}

void Rendering::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_shaderProgram.use();
    m_camera.bindViewMatrix(m_shaderProgram.getUniformLocation("viewMatrix"));
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
