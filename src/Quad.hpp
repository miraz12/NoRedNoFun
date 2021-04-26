#pragma once

#include "GraphicsObject.hpp"

class ShaderProgram;

class Quad: protected GraphicsObject {
public:
    Quad(ShaderProgram &shaderProgram);
    virtual ~Quad();

    virtual void draw();

private:
    float m_vertices[32] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    };

    unsigned int m_indices[6] = {
        0, 1, 2,
        2, 1, 3,
    };

    unsigned char m_texData[16] = {
        255, 255, 255, 255, 0, 0, 0, 255,
        0, 0, 0, 255, 255, 255, 255, 255
    };
};
