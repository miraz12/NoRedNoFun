#include "SpriteMap.hpp"

SpriteMap::SpriteMap(std::vector<glm::mat4>* matrices, unsigned int matrixIndex):
	m_matrices(matrices),
	m_matrixIndex(matrixIndex),
	m_nrOfSprites(1.0f),
	m_currentSprite(0.0f) {

}

SpriteMap::~SpriteMap() {

}

const glm::vec2 &SpriteMap::getNrOfSprites() {
	return m_nrOfSprites;
}

const glm::vec2 &SpriteMap::getCurrentSprite() {
	return m_currentSprite;
}

glm::mat4& SpriteMap::getTextureMatrix() {
	return m_matrices->at(m_matrixIndex);
}

void SpriteMap::setNrOfSprites(float x, float y) {
	m_nrOfSprites.x = x;
	m_nrOfSprites.y = y;
	updateTextureMatrix();
}

void SpriteMap::setCurrentSprite(float x, float y) {
	m_currentSprite.x = x;
	m_currentSprite.y = y;
	updateTextureMatrix();
}

void SpriteMap::advanceSpriteBy(float x, float y) {
	m_currentSprite.x += x;
	m_currentSprite.y += y;
	updateTextureMatrix();
}

void SpriteMap::updateTextureMatrix() {
	glm::mat4 &tempMatrix = m_matrices->at(m_matrixIndex);
	tempMatrix = glm::mat4(1.0f);
	glm::vec2 spriteSize = glm::vec2(1.0f / glm::max(m_nrOfSprites.x, 0.000001f), 1.0f / glm::max(m_nrOfSprites.y, 0.000001f));
	tempMatrix = glm::translate(tempMatrix, glm::vec3(m_currentSprite * spriteSize, 0.0f));
	tempMatrix = glm::scale(tempMatrix, glm::vec3(spriteSize, 1.0f));
}
