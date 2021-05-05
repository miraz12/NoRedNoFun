#pragma once

#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpriteMap : public Texture {
public:
	SpriteMap(unsigned int textureIndex);
	~SpriteMap();

	void setNrOfSprites(int x, int y);
	void setCurrentSprite(int x, int y);

	void bindTextureMatrix(unsigned int uniformLocation);
private:
	glm::vec2 m_numSprites;
	glm::vec2 m_currentSprite;
	bool m_matrixNeedsUpdate;

	glm::mat4 m_textureMatrix;
};