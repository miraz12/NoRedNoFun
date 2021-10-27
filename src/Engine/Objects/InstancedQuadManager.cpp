#include "InstancedQuadManager.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

InstancedQuadManager::InstancedQuadManager(ShaderProgram &shaderProgram):
	GraphicsObject(shaderProgram) {
    
    for (unsigned int i = 0; i < 15; i++) {
        m_textures.emplace_back(new Texture(i));
    }

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

    for (size_t i = 0; i < m_textures.size(); i++) {
        delete m_textures[i];
    }
}


Quad* InstancedQuadManager::getNewQuad() {
    unsigned int newQuadIndex;
    if (m_availableQuads.size() > 0) {
        m_quadData[m_availableQuads[0]].modelMatrix = glm::mat4(1.0f);
        m_quadData[m_availableQuads[0]].textureMatrix = glm::mat4(1.0f);
        m_quadData[m_availableQuads[0]].textureIndex = 0;
        newQuadIndex = m_availableQuads[0];
        m_availableQuads.erase(m_availableQuads.begin());
    }
    else {
        m_quadData.emplace_back();
        newQuadIndex = (unsigned int) (m_quadData.size() - 1);
    }

	m_quads.emplace_back(new Quad(&m_quadData, newQuadIndex));

    return m_quads[m_quads.size() - 1];
}

std::vector<Quad*>& InstancedQuadManager::getQuads() {
	return m_quads;
}

void InstancedQuadManager::reset()
{
    for (size_t i = 0; i < m_quads.size(); i++) {
        delete m_quads[i];
    }
    m_quads.clear();
    m_quadData.clear();
    m_availableQuads.clear();

}

Texture& InstancedQuadManager::getTexture(unsigned int textureId) {
    return *(m_textures[textureId]);
}

void InstancedQuadManager::returnQuad(Quad* quadToReturn) {
    for (size_t i = 0; i < m_quads.size(); i++) {
        if (m_quads[i] == quadToReturn) {
            quadToReturn->getModelMatrix() = glm::mat4(0.0f);
            m_availableQuads.emplace_back(quadToReturn->getQuadIndex());
            delete quadToReturn;
            m_quads.erase(m_quads.begin() + i);
        }
    }
}

void InstancedQuadManager::draw() {
    bindVAO();

	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, m_quadData.size() * sizeof(InstanceData), &m_quadData[0], GL_DYNAMIC_DRAW);

    for (size_t i = 0; i < m_textures.size(); i++) {
	    m_textures[i]->bind();
    }

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei) m_quadData.size());
//     glDrawArraysInstanced(GL_TRIANGLES, 0, 6, m_quadMatrices.size());
}
