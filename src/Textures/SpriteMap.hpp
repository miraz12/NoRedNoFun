#pragma once

#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpriteMap {
public:
	SpriteMap(glm::mat4& textureMatrix);
	virtual ~SpriteMap();

	virtual const glm::vec2& getNrOfSprites();
	virtual const glm::vec2& getCurrentSprite();
	virtual glm::mat4& getTextureMatrix();

	virtual void setNrOfSprites(float x, float y);
	virtual void setCurrentSprite(float x, float y);
	virtual void advanceSpriteBy(float x, float y);
private:
	void updateTextureMatrix();

	glm::vec2 m_nrOfSprites;
	glm::vec2 m_currentSprite;

	glm::mat4 &m_textureMatrix;
};
