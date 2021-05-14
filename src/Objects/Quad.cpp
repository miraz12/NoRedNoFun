#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

#include "InstancedQuadManager.hpp"

Quad::Quad(glm::mat4 &modelMatrix, glm::mat4 &textureMatrix, InstancedQuadManager *owner):
    m_modelMatrix(modelMatrix),
	m_spriteMap(textureMatrix),
	m_owner(owner) {

}

Quad::~Quad() {

}

glm::mat4& Quad::getModelMatrix() {
	return m_modelMatrix;
}

SpriteMap& Quad::getSpriteMap() {
	return m_spriteMap;
}