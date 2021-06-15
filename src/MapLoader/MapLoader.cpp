#include "MapLoader.hpp"
#include <glad/glad.h>

MapLoader::MapLoader(ShaderProgram &shader) : m_modelMat(1.0f), m_textureMat(1.0f),
                         m_quad(m_modelMat, m_textureMat),
                         m_texture(1), GraphicsObject(shader) { //TODO: Maybe have a texture mgr?

    m_texture.setTextureData(m_mapData, 10, 10); //TODO: This isn't correct..
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

MapLoader::~MapLoader() {}


void MapLoader::draw() {
    m_shader.use();
    bindVAO();
    m_texture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
