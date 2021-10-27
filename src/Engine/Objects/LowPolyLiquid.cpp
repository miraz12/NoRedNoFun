#include "LowPolyLiquid.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

LowPolyLiquid::LowPolyLiquid(ShaderProgram& shaderProgram):
    GraphicsObject(shaderProgram),
    m_currentColor({0.0f, 0.0f, 1.0f, 0.7f}) {

}

LowPolyLiquid::~LowPolyLiquid() {

}

void LowPolyLiquid::setCurrentColor(glm::vec4 color) {
    m_currentColor = color;
}

void LowPolyLiquid::addStop(glm::vec3 position) {
    m_vertices.emplace_back(position.x);
    m_vertices.emplace_back(position.y);
    m_vertices.emplace_back(position.z);
    m_vertices.emplace_back(m_currentColor.x);
    m_vertices.emplace_back(m_currentColor.y);
    m_vertices.emplace_back(m_currentColor.z);
    m_vertices.emplace_back(m_currentColor.w);
    m_vertices.emplace_back(0.0f);
    m_vertices.emplace_back(0.0f);

    setVertexData(sizeof(float) * m_vertices.size(), m_vertices.data());
}

void LowPolyLiquid::draw() {
    bindVAO();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) (m_vertices.size()/9));
}
