#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

Quad::Quad(std::vector<glm::mat4>* matrices, unsigned int matrixIndex) :
    SpriteMap(matrices, matrixIndex + 1),
    m_matrices(matrices),
    m_matrixIndex(matrixIndex) {

}

Quad::~Quad() {

}

glm::mat4& Quad::getModelMatrix() {
	return m_matrices->at(m_matrixIndex);
}

unsigned int Quad::getMatrixIndex() {
    return m_matrixIndex;
}