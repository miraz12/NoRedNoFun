#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

#include "Engine/Objects/InstancedQuadManager.hpp"

Quad::Quad(std::vector<InstanceData> *quadData, unsigned int quadIndex) :
    SpriteMap(quadData, quadIndex),
    m_quadData(quadData),
    m_quadIndex(quadIndex) {

}

Quad::~Quad() {

}

glm::mat4& Quad::getModelMatrix() {
	return m_quadData->at(m_quadIndex).modelMatrix;
}

unsigned int Quad::getQuadIndex() {
    return m_quadIndex;
}

void Quad::setTextureIndex(unsigned int index) {
    m_quadData->at(m_quadIndex).textureIndex = index;
}
