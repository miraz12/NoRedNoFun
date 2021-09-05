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
    for (size_t i = 0; i < m_quads.size(); i++) {
        delete m_quads[i];
    }
}


Quad* InstancedQuadManager::getNewQuad() {
    unsigned int newMatrixIndex;
    if (m_availableMatrices.size() > 0) {
        m_quadMatrices[m_availableMatrices[0]] = glm::mat4(1.0f);
        m_quadMatrices[m_availableMatrices[0] + 1] = glm::mat4(1.0f);
        newMatrixIndex = m_availableMatrices[0];
        m_availableMatrices.erase(m_availableMatrices.begin());
    }
    else {
        m_quadMatrices.emplace_back(1.0f);
        m_quadMatrices.emplace_back(1.0f);
        newMatrixIndex = (unsigned int) (m_quadMatrices.size() - 2);
    }

	m_quads.emplace_back(new Quad(&m_quadMatrices, newMatrixIndex));

    return m_quads[m_quads.size() - 1];
}

std::vector<Quad*>& InstancedQuadManager::getQuads() {
	return m_quads;
}

Texture& InstancedQuadManager::getTexture() {
    return m_texture;
}

void InstancedQuadManager::returnQuad(Quad* quadToReturn) {
    for (size_t i = 0; i < m_quads.size(); i++) {
        if (m_quads[i] == quadToReturn) {
            quadToReturn->getModelMatrix() = glm::mat4(0.0f);
            m_availableMatrices.emplace_back(quadToReturn->getMatrixIndex());
            delete quadToReturn;
            m_quads.erase(m_quads.begin() + i);
        }
    }
}

void InstancedQuadManager::draw() {
    bindVAO();

	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, m_quadMatrices.size() * sizeof(glm::mat4), m_quadMatrices.data(), GL_DYNAMIC_DRAW);

	m_texture.bind();

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei) (m_quadMatrices.size() / 2));
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_quadMatrices.size());
}
