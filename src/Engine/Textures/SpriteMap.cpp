#include "SpriteMap.hpp"

SpriteMap::SpriteMap(glm::mat4 &textureMatrix):
	m_nrOfSprites(1.0f),
	m_currentSprite(0.0f),
	m_textureMatrix(textureMatrix) {

}

SpriteMap::~SpriteMap() {

}

const glm::vec2 &SpriteMap::getNrOfSprites() {
	return m_nrOfSprites;
}

const glm::vec2 &SpriteMap::getCurrentSprite() {
	return m_currentSprite;
}

glm::mat4 &SpriteMap::getTextureMatrix() {
	return m_textureMatrix;
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
	m_textureMatrix = glm::mat4(1.0f);
	glm::vec2 spriteSize = glm::vec2(1.0f / glm::max(m_nrOfSprites.x, 0.000001f), 1.0f / glm::max(m_nrOfSprites.y, 0.000001f));
	m_textureMatrix = glm::translate(m_textureMatrix, glm::vec3(m_currentSprite * spriteSize, 0.0f));
	m_textureMatrix = glm::scale(m_textureMatrix, glm::vec3(spriteSize, 1.0f));
}
