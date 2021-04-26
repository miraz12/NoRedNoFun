#include "Pen.hpp"

#include <glad/glad.h>

#include "GraphicsObject.hpp"
#include "ShaderProgram.hpp"

Pen::Pen(ShaderProgram& shaderProgram):
    GraphicsObject(shaderProgram),
    m_currentColor({1.0f, 1.0f, 1.0f}) {

}

Pen::~Pen() {

}

void Pen::setCurrentColor(glm::vec3 color) {
    m_currentColor = color;
}

void Pen::addStop(glm::vec3 position) {
    m_vertices.emplace_back(position.x);
    m_vertices.emplace_back(position.y);
    m_vertices.emplace_back(position.z);
    m_vertices.emplace_back(m_currentColor.x);
    m_vertices.emplace_back(m_currentColor.y);
    m_vertices.emplace_back(m_currentColor.z);
    m_vertices.emplace_back(0.0f);
    m_vertices.emplace_back(0.0f);

    setVertexData(sizeof(float) * m_vertices.size(), m_vertices.data());
}

void Pen::draw() {
    prepareDraw();
    glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size()/8); // GL_LINE_STRIP can be changed to other primative modes like GL_TRIANGLES or GL_POINT
}
