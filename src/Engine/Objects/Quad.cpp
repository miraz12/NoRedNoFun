#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

#include "InstancedQuadManager.hpp"

Quad::Quad(glm::mat4& modelMatrix, glm::mat4& textureMatrix) :
    SpriteMap(textureMatrix),
    m_modelMatrix(modelMatrix) {

}

Quad::~Quad() {

}

glm::mat4& Quad::getModelMatrix() {
	return m_modelMatrix;
}