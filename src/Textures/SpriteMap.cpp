#include "SpriteMap.hpp"

#include <glad/glad.h>

SpriteMap::SpriteMap(unsigned int textureIndex) : Texture(textureIndex) {
	m_matrixNeedsUpdate = false;
}

SpriteMap::~SpriteMap() {

}

void SpriteMap::setNrOfSprites(int x, int y) {
	m_numSprites.x = (float) x;
	m_numSprites.y = (float) y;
	m_matrixNeedsUpdate = true;
}

void SpriteMap::setCurrentSprite(int x, int y) {
	m_currentSprite.x = (float) x;
	m_currentSprite.y = (float) y;
	m_matrixNeedsUpdate = true;
}

void SpriteMap::bindTextureMatrix(unsigned int uniformLocation) {
	if (m_matrixNeedsUpdate) {
		m_textureMatrix = glm::mat4(1.0f);
		m_textureMatrix = glm::translate(m_textureMatrix, glm::vec3(m_currentSprite.x - 1, m_currentSprite.y - 1, 0.0f));
		m_textureMatrix = glm::scale(m_textureMatrix, glm::vec3(1.0f / glm::max(m_numSprites.x, 1.0f), 1.0f / glm::max(m_numSprites.y, 1.0f), 1.0f));
		m_matrixNeedsUpdate = false;
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_textureMatrix));
}