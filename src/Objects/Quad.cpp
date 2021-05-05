#include "Quad.hpp"

#include <glad/glad.h>

#include "GraphicsObject.hpp"
#include "../ShaderPrograms/ShaderProgram.hpp"

Quad::Quad(ShaderProgram& shaderProgram):
    GraphicsObject(shaderProgram) {
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);

    p_texture.setTextureData(m_texData, 2, 2);
    p_texture.enableTexture(true);
}

Quad::~Quad() {

}

void Quad::draw() {
    prepareDraw();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Using indices, call setIndexData().
//     glDrawArrays(GL_TRIANGLES, 0, 6); // Not using indices, don't call setIndexData().
}
