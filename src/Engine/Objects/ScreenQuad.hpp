#pragma once

#include "GraphicsObject.hpp"

class ScreenQuad : protected GraphicsObject {
public:
    ScreenQuad(ShaderProgram &shaderProgram);
    ~ScreenQuad() = default;

    void setTexture(unsigned int texId) { m_texture = texId; };
    void draw();

private:

    unsigned int m_texture;
	unsigned int m_vbo;
    float m_quadVertices[24] = { 
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
};