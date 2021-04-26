#include "Rendering.hpp"

#include <iostream>
#include <glad/glad.h>

Rendering::Rendering():
    m_canvas(m_shaderProgram),
    m_quad(m_shaderProgram),
    m_pen(m_shaderProgram) {
    initGL();
}

Rendering::~Rendering() {

}

Canvas& Rendering::getCanvas() {
    return m_canvas;
}

Pen& Rendering::getPen() {
    return m_pen;
}

void Rendering::draw() {
    m_shaderProgram.use();

    m_canvas.clear();
    m_canvas.applyCanvasMatrix();

    m_quad.draw();
    m_pen.draw();
}

void Rendering::initGL() {
    m_canvas.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Back-face culling
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

//     glEnable(GL_LINE_SMOOTH); // Line antialiasing
    glLineWidth(3.0f); // Sets line width of things like wireframe and draw lines
    glPointSize(3.0f);
}
