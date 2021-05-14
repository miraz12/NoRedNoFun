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


Quad* InstancedQuadManager::getNewQuad() {
    m_quadMatrices.emplace_back(1.0f);
    m_quadMatrices.emplace_back(1.0f);

	m_quads.emplace_back(m_quadMatrices[m_quadMatrices.size() - 2], m_quadMatrices.back(), this);
    m_bufferNeedsUpdate = true;

    return &(m_quads.back());
}

std::vector<Quad>& InstancedQuadManager::getQuads() {
	return m_quads;
}

void InstancedQuadManager::notifyUpdate() {
	m_bufferNeedsUpdate = true;
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
