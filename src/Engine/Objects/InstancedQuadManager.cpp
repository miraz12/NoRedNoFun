#include "InstancedQuadManager.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../ShaderPrograms/ShaderProgram.hpp"


InstancedQuadManager::InstancedQuadManager(ShaderProgram &shaderProgram):
	GraphicsObject(shaderProgram),
	m_texture(0) {
	
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

	m_quads.emplace_back(m_quadMatrices[m_quadMatrices.size() - 2], m_quadMatrices.back());

    return &(m_quads.back());
}

std::vector<Quad>& InstancedQuadManager::getQuads() {
	return m_quads;
}

Texture& InstancedQuadManager::getTexture() {
    return m_texture;
}

void InstancedQuadManager::draw() {
    bindVAO();

	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, m_quadMatrices.size() * sizeof(glm::mat4), m_quadMatrices.data(), GL_DYNAMIC_DRAW);

	m_texture.bind();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei) (m_quadMatrices.size() / 2));
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_quadMatrices.size());
}
