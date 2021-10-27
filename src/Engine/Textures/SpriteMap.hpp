#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

struct InstanceData;

class SpriteMap {
public:
	SpriteMap(std::vector<InstanceData>* quadData, unsigned int quadIndex);
	virtual ~SpriteMap();

	virtual const glm::vec2& getNrOfSprites();
	virtual const glm::vec2& getCurrentSprite();
	virtual glm::mat4& getTextureMatrix();

	virtual void setNrOfSprites(float x, float y);
	virtual void setCurrentSprite(float x, float y);
	virtual void advanceSpriteBy(float x, float y);
private:
	void updateTextureMatrix();

	std::vector<InstanceData>* m_quadData;
	unsigned int m_quadIndex;

	glm::vec2 m_nrOfSprites;
	glm::vec2 m_currentSprite;
};
