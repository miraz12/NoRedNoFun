#include "InstancedQuadManager.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../ShaderPrograms/ShaderProgram.hpp"


InstancedQuadManager::InstancedQuadManager(ShaderProgram &shaderProgram):
	GraphicsObject(shaderProgram),
	m_spriteMap(0),
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
    m_quadInstances.emplace_back();
    m_quadInstances.emplace_back();
    m_bufferNeedsUpdate = true;
    return m_quadInstances.size() - 2;
}

void InstancedQuadManager::setModelMatrix(unsigned int quadIndex, glm::mat4 matrix) {
    if (quadIndex < m_quadInstances.size()) {
        m_quadInstances[quadIndex] = matrix;
        m_bufferNeedsUpdate = true;
    }
}

void InstancedQuadManager::setTextureMatrix(unsigned int quadIndex, glm::mat4 matrix) {
    if (quadIndex < m_quadInstances.size()) {
        m_quadInstances[quadIndex + 1] = matrix;
        m_bufferNeedsUpdate = true;
    }
}

void InstancedQuadManager::draw() {
    bindVAO();
    if (m_bufferNeedsUpdate) {
        glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, m_quadInstances.size() * sizeof(glm::mat4), m_quadInstances.data(), GL_STATIC_DRAW);
        m_bufferNeedsUpdate = false;
    }

	m_spriteMap.bindSprite();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 1); // Use texture

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_quadInstances.size());
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_quadInstances.size());
}
