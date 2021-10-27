#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../ShaderPrograms/ShaderProgram.hpp"

class GraphicsObject {
public:
    GraphicsObject(ShaderProgram& ShaderProgram);
    virtual ~GraphicsObject();

    void changeShaderProgram(ShaderProgram &shaderProgram);
    void bindVAO();
    void unbindVAO();
    virtual void draw() = 0;

protected:
    ShaderProgram& p_shaderProgram;

    virtual void setVertexData(std::size_t dataSize, const void* data);
    virtual void setIndexData(std::size_t dataSize, const void* data);
private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO; // Optional

    void init();
};
