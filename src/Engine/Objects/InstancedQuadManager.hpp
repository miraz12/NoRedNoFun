#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "GraphicsObject.hpp"
#include "Quad.hpp"
#include "../Textures/Texture.hpp"

struct InstanceData {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 textureMatrix = glm::mat4(1.0f);
    int textureIndex = 0;
};

class InstancedQuadManager : protected GraphicsObject {
public:
	InstancedQuadManager(ShaderProgram &shaderProgram);
	~InstancedQuadManager();
    
    Quad* getNewQuad();
	std::vector<Quad*>& getQuads();

    //resets data for a new start
    void reset();

    Texture& getTexture(unsigned int textureId);

    void returnQuad(Quad* quadToReturn);
    void draw();
private:
	unsigned int m_instanceVBO;

    std::vector<InstanceData> m_quadData;
    std::vector<unsigned int> m_availableQuads;
	std::vector<Quad*> m_quads;

    std::vector<Texture*> m_textures;

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
