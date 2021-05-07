#include "SpriteMap.hpp"

#include <glad/glad.h>

SpriteMap::SpriteMap(unsigned int textureIndex) : Texture(textureIndex),
m_nrOfSprites(1.0f),
	m_currentSprite(0.0f),
	m_textureMatrix(1.0f),
	m_matrixNeedsUpdate(false) {

}

SpriteMap::~SpriteMap() {

}

glm::vec2 &SpriteMap::getNrOfSprites() {
	return m_nrOfSprites;
}

glm::vec2 &SpriteMap::getCurrentSprite() {
	return m_currentSprite;
}

void SpriteMap::setNrOfSprites(float x, float y) {
	m_nrOfSprites.x = x;
	m_nrOfSprites.y = y;
	m_matrixNeedsUpdate = true;
}

void SpriteMap::setCurrentSprite(float x, float y) {
	m_currentSprite.x = x;
	m_currentSprite.y = y;
	m_matrixNeedsUpdate = true;
}

void SpriteMap::advanceSpriteBy(float x, float y) {
	m_currentSprite.x += x;
	m_currentSprite.y += y;
	m_matrixNeedsUpdate = true;
}

void SpriteMap::notifyChange() {
	m_matrixNeedsUpdate = true;
}

void SpriteMap::bindSprite(unsigned int uniformLocation) {
	bind(); // Bind underlaying texture
	if (m_matrixNeedsUpdate) {
		m_textureMatrix = glm::mat4(1.0f);
		glm::vec2 spriteSize = glm::vec2(1.0f / glm::max(m_nrOfSprites.x, 1.0f), 1.0f / glm::max(m_nrOfSprites.y, 1.0f));
		m_textureMatrix = glm::translate(m_textureMatrix, glm::vec3(m_currentSprite * spriteSize, 0.0f));
		m_textureMatrix = glm::scale(m_textureMatrix, glm::vec3(spriteSize, 1.0f));
		m_matrixNeedsUpdate = false;
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_textureMatrix));
}