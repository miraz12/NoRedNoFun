#include "MapLoader.hpp"
#include <glad/glad.h>

MapLoader::MapLoader(ShaderProgram &shader) : m_modelMat(1.0f), m_textureMat(1.0f),
                         m_quad(m_modelMat, m_textureMat),
                         m_texture(1), GraphicsObject(shader) { //TODO: Maybe have a texture mgr?

    m_width = 10;
    m_height = 10;
    parseMap();
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

MapLoader::~MapLoader() {}


void MapLoader::draw() {
    m_shader.use();
    bindVAO();
    glUniform1i(m_shader.getUniformLocation("useTexture"), 1);
    m_texture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MapLoader::parseMap() {
    unsigned char* texData;
    texData = (unsigned char *) malloc(sizeof(unsigned char) * m_width * m_width);
    for (size_t i = 0; i < m_width*m_width; i++) {
        switch (m_mapData[i]) {
        case tileType::ground:
            texData[i] = 0;
            break;
        case tileType::wall:
            texData[i] = 255;
            break;
        }
    }
    m_texture.setTextureData(texData, 10, 10); 
}
