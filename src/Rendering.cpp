#include "Rendering.hpp"

#include <iostream>
#include <glad/glad.h>

Rendering::Rendering(): m_quad(m_shaderProgram) {
    initGL();
    m_camera.setPosition(0.0f, 0.0f);
    m_camera.setZoom(0.5f);
    m_camera.setRotation(0.0f);
}

Rendering::~Rendering() {

}

void Rendering::update(float dt) {
	m_quad.update(dt);
}

void Rendering::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_shaderProgram.use();
    m_camera.bindViewMatrix(m_shaderProgram.getUniformLocation("viewMatrix"));
    m_quad.draw();
}

void Rendering::initGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Back-face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

//     glEnable(GL_LINE_SMOOTH); // Line antialiasing
    glLineWidth(3.0f); // Sets line width of things like wireframe and draw lines
    glPointSize(3.0f);
}
