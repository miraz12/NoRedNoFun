#pragma once

#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SpriteMap : public Texture {
public:
	SpriteMap(unsigned int textureIndex);
	~SpriteMap();

	glm::vec2& getNrOfSprites();
	glm::vec2& getCurrentSprite();
    glm::mat4& getTextureMatrix();

	void setNrOfSprites(float x, float y);
	void setCurrentSprite(float x, float y);
	void advanceSpriteBy(float x, float y);

	void notifyChange(); // Call this if you update data through the references returned by getNrOfSprites and getCurrentSprite

	void bindSprite(); // Binds texture matrix and underlying texture
private:
	glm::vec2 m_nrOfSprites;
	glm::vec2 m_currentSprite;
	bool m_matrixNeedsUpdate;

	glm::mat4 m_textureMatrix;
};
