#pragma once

#include "GraphicsObject.hpp"
#include "../Textures/SpriteMap.hpp"

class ShaderProgram;

class Quad: protected GraphicsObject {
public:
    Quad(ShaderProgram &shaderProgram);
    virtual ~Quad();


	void update(float dt);
    virtual void draw();

private:
    unsigned int m_useTexture;
    glm::mat4 m_modelMatrix;

	SpriteMap m_spriteMap;
	float m_updateTextureTimer;

    float m_vertices[36] = {
//		Position				Color						Texture coords
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
    };

    unsigned int m_indices[6] = {
        0, 1, 2,
        2, 1, 3,
    };
};
