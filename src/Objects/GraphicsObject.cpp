#include "GraphicsObject.hpp"

#include "../ShaderPrograms/ShaderProgram.hpp"

#include <glad/glad.h>

GraphicsObject::GraphicsObject(ShaderProgram& shaderProgram):
    p_shaderProgram(shaderProgram){
    init();
}

GraphicsObject::~GraphicsObject() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void GraphicsObject::changeShaderProgram(ShaderProgram& shaderProgram) {
    p_shaderProgram = shaderProgram;
}

void GraphicsObject::bindVAO() {
    glBindVertexArray(m_VAO);
}

void GraphicsObject::unbindVAO() {
	glBindVertexArray(0);
}

void GraphicsObject::setVertexData(std::size_t dataSize, const void* data) {
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void GraphicsObject::setIndexData(std::size_t dataSize, const void* data) {
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO),
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void GraphicsObject::init() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	p_shaderProgram.setupVertexAttributePointers();

	glBindVertexArray(0);
}
