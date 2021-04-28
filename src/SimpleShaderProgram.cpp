#include "SimpleShaderProgram.hpp"

#include <iostream>

#include <glad/glad.h>

SimpleShaderProgram::SimpleShaderProgram():
    ShaderProgram("../src/Shaders/vertex.glsl", "../src/Shaders/fragment.glsl") {

    // Change if uniforms change in shaders
    m_nrOfUniforms = 3;
    m_uniformBindings = new std::pair<std::string, unsigned int>[m_nrOfUniforms];
    m_uniformBindings[0] = std::pair<std::string, unsigned int>("modelMatrix", glGetUniformLocation(p_shaderProgram, "modelMatrix"));
    m_uniformBindings[1] = std::pair<std::string, unsigned int>("viewMatrix", glGetUniformLocation(p_shaderProgram, "viewMatrix"));
    m_uniformBindings[2] = std::pair<std::string, unsigned int>("useTexture", glGetUniformLocation(p_shaderProgram, "useTexture"));
}

SimpleShaderProgram::~SimpleShaderProgram() {
    delete[] m_uniformBindings;
}

void SimpleShaderProgram::setupVertexAttributePointers() {
    // Change if input layout changes in shaders
//     unsigned int positionLocation = glGetAttribLocation(p_shaderProgram, "inPosition");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

//     unsigned int colorLocation = glGetAttribLocation(p_shaderProgram, "inColor");
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

//     unsigned int texCoordsLocation = glGetAttribLocation(p_shaderProgram, "inTexCoords");
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

unsigned int SimpleShaderProgram::getUniformLocation(std::string uniformName) {
    for (unsigned int i = 0; i < m_nrOfUniforms; i++) {
        if (m_uniformBindings[i].first == uniformName) {
            return m_uniformBindings[i].second;
        }
    }

    std::cout << "No uniform with name " << uniformName << "\n";
    return NULL;
}
