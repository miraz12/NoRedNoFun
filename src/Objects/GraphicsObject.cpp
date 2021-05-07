#include "GraphicsObject.hpp"

#include "../ShaderPrograms/ShaderProgram.hpp"

#include <glad/glad.h>

GraphicsObject::GraphicsObject(ShaderProgram& shaderProgram):
    p_shaderProgram(shaderProgram),
    m_modelMatrix(1.0f),
	m_useTexture(false) {
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

void GraphicsObject::setModelMatrix(glm::mat4 modelMatrix) {
    m_modelMatrix = modelMatrix;
}

void GraphicsObject::bindIdentityTextureMatrix() {
	glUniformMatrix4fv(p_shaderProgram.getUniformLocation("textureMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
}

void GraphicsObject::setUseTexture(bool useTexture) {
	m_useTexture = useTexture;
}

void GraphicsObject::prepareDraw() {
    glBindVertexArray(m_VAO);

    glUniformMatrix4fv(p_shaderProgram.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

	glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), m_useTexture);
}

void GraphicsObject::setVertexData(std::size_t dataSize, const void* data) {
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);

    p_shaderProgram.setupVertexAttributePointers();

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

}
