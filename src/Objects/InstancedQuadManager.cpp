#include "InstancedQuadManager.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../ShaderPrograms/ShaderProgram.hpp"


InstancedQuadManager::InstancedQuadManager(ShaderProgram &shaderProgram):
	GraphicsObject(shaderProgram),
	m_texture(0),
	m_bufferNeedsUpdate(false) {
	
    bindVAO();
	glGenBuffers(1, &m_instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO); 
    p_shaderProgram.setupInstancedVertexAttributePointers();
    unbindVAO();

    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

InstancedQuadManager::~InstancedQuadManager() {

}


unsigned int InstancedQuadManager::getNewQuadIndex() {
    m_quadMatrices.emplace_back(1.0f);
    m_quadMatrices.emplace_back(1.0f);
    m_bufferNeedsUpdate = true;
    return (unsigned int) (m_quadMatrices.size() - 2);
}

void InstancedQuadManager::setModelMatrix(unsigned int quadIndex, glm::mat4 matrix) {
    if (quadIndex < m_quadMatrices.size()) {
        m_quadMatrices[quadIndex] = matrix;
        m_bufferNeedsUpdate = true;
    }
}

void InstancedQuadManager::setTextureMatrix(unsigned int quadIndex, glm::mat4 matrix) {
    if (quadIndex < m_quadMatrices.size()) {
        m_quadMatrices[(size_t) quadIndex + 1] = matrix;
        m_bufferNeedsUpdate = true;
    }
}

void InstancedQuadManager::draw() {
    bindVAO();
    if (m_bufferNeedsUpdate) {
        glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, m_quadMatrices.size() * sizeof(glm::mat4), m_quadMatrices.data(), GL_STATIC_DRAW);
        m_bufferNeedsUpdate = false;
    }

	m_texture.bind();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 1); // Use texture

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_quadMatrices.size() / 2);
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_quadMatrices.size());
}
