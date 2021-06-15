#pragma once

#include "GraphicsObject.hpp"
#include "../Textures/SpriteMap.hpp"

class ShaderProgram;
class InstancedQuadManager;

class Quad: public SpriteMap {
public:
    Quad(glm::mat4& modelMatrix, glm::mat4& textureMatrix, InstancedQuadManager* owner);
    Quad(glm::mat4& modelMatrix, glm::mat4& textureMatrix);
    virtual ~Quad();

	glm::mat4& getModelMatrix();
private:
    glm::mat4 &m_modelMatrix;

	InstancedQuadManager* m_owner;
};
