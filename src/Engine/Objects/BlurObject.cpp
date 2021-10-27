#include "BlurObject.hpp"
#include <glad/glad.h>


BlurObject::BlurObject(ShaderProgram &shaderProgram) : GraphicsObject(shaderProgram) {
    bindVAO();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    setVertexData(sizeof(m_quadVertices), m_quadVertices);
    p_shaderProgram.setupVertexAttributePointers();
    unbindVAO();
}

void BlurObject::draw() {
    bindVAO();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureV);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BlurObject::drawH() {
    bindVAO();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureH);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}