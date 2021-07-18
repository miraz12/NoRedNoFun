#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class InstancedQuadManager;

class SpriteMap {
public:
	SpriteMap(std::vector<glm::mat4>* matrices, unsigned int matrixIndex);
	virtual ~SpriteMap();

	virtual const glm::vec2& getNrOfSprites();
	virtual const glm::vec2& getCurrentSprite();
	virtual glm::mat4& getTextureMatrix();

	virtual void setNrOfSprites(float x, float y);
	virtual void setCurrentSprite(float x, float y);
	virtual void advanceSpriteBy(float x, float y);
private:
	void updateTextureMatrix();

	std::vector<glm::mat4>* m_matrices;
	unsigned int m_matrixIndex;

	glm::vec2 m_nrOfSprites;
	glm::vec2 m_currentSprite;
};
