#pragma once

#include "GraphicsObject.hpp"

class BlurObject : protected GraphicsObject {
public:
    BlurObject(ShaderProgram &shaderProgram);
    ~BlurObject() = default;

    void setTextures(unsigned int texIdV, unsigned int texIdH) { m_textureV = texIdV; m_textureH = texIdH; };
    void draw();
    void drawH();

private:

    unsigned int m_textureV;
    unsigned int m_textureH;
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