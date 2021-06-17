#pragma once

#include "GraphicsObject.hpp"
#include "../Textures/SpriteMap.hpp"

class ShaderProgram;
class InstancedQuadManager;

class Quad: public SpriteMap {
public:
    Quad(glm::mat4& modelMatrix, glm::mat4& textureMatrix);
    virtual ~Quad();

	void translate(glm::vec3 &translation);
	void setTranslation(glm::vec3& translation);

	glm::mat4& getModelMatrix();
private:
	glm::vec3 m_translation;
    glm::mat4 &m_modelMatrix;
};
