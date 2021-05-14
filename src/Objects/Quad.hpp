#pragma once

#include "GraphicsObject.hpp"
#include "../Textures/SpriteMap.hpp"

class ShaderProgram;
class InstancedQuadManager;

class Quad{
public:
    Quad(glm::mat4 &modelMatrix, glm::mat4& textureMatrix, InstancedQuadManager* owner);
    virtual ~Quad();

	glm::mat4& getModelMatrix();
	SpriteMap& getSpriteMap();

	// TODO: Add functions for updating model matrix and sprite map that automatically calls owner->notifyUpdate()

private:
    glm::mat4 &m_modelMatrix;
	SpriteMap m_spriteMap;

	InstancedQuadManager* m_owner;
};
