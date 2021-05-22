#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "GraphicsObject.hpp"
#include "Quad.hpp"
#include "../Textures/Texture.hpp"

class ShaderProgram;

class InstancedQuadManager : protected GraphicsObject {
public:
	InstancedQuadManager(ShaderProgram &shaderProgram);
	~InstancedQuadManager();

    Quad* getNewQuad();
	std::vector<Quad>& getQuads();

    void draw();
private:
	unsigned int m_instanceVBO;

    std::vector<glm::mat4> m_quadMatrices;
	std::vector<Quad> m_quads;

    Texture m_texture;

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
