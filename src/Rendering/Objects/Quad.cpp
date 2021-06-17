#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

#include "InstancedQuadManager.hpp"

Quad::Quad(glm::mat4 &modelMatrix, glm::mat4 &textureMatrix) :
    SpriteMap(textureMatrix),
	m_translation(0.0f),
    m_modelMatrix(modelMatrix) {}

void Quad::translate(glm::vec3& translation) {
	m_modelMatrix = glm::translate(m_modelMatrix, translation);
}

void Quad::setTranslation(glm::vec3& translation) {
	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix = glm::translate(m_modelMatrix, translation);
}

Quad::~Quad() {}

glm::mat4& Quad::getModelMatrix() {
	return m_modelMatrix;
}
