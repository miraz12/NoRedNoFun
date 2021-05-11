#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "GraphicsObject.hpp"
#include "../Textures/SpriteMap.hpp"

class ShaderProgram;

class InstancedQuadManager : protected GraphicsObject {
public:
	InstancedQuadManager(ShaderProgram &shaderProgram);
	~InstancedQuadManager();

    unsigned int getNewQuadIndex();

    void setModelMatrix(unsigned int quadIndex, glm::mat4 matrix);
    void setTextureMatrix(unsigned int quadIndex, glm::mat4 matrix);

    void draw();
private:
	unsigned int m_instanceVBO;

    struct QuadInstance{
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 textureMatrix = glm::mat4(1.0f);
    };
    std::vector<glm::mat4> m_quadInstances;

    SpriteMap m_spriteMap;
    bool m_bufferNeedsUpdate;

    float m_vertices[20] = {
//		Position				Texture coords
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f, 0.0f,	    1.0f, 0.0f,
    };

    unsigned int m_indices[6] = {
        0, 1, 2,
        2, 1, 3,
    };
};
