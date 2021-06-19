#include "MapLoader.hpp"
#include <glad/glad.h>

MapLoader::MapLoader(ShaderProgram &shader) : m_modelMat(1.0f), m_textureMat(1.0f),
                         m_texture(0), GraphicsObject(shader), m_width(30), m_height(30) { 

    parseMap();
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

MapLoader::~MapLoader() {

}

glm::mat4& MapLoader::getModelMatrix() {
	return m_modelMat;
}

void MapLoader::draw() {
    p_shaderProgram.use();
    bindVAO();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 1);
	glUniformMatrix4fv(p_shaderProgram.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(m_modelMat));
    m_texture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MapLoader::parseMap() {
    unsigned char* texData;
    texData = (unsigned char *) malloc(sizeof(unsigned char) * m_width * m_height * 4);
    for (size_t i = 0; i < m_width*m_height; i++) {
        switch (m_mapData[i]) {
        case tileType::ground:
            texData[i*4]   = 200;
            texData[i*4+1] = 200;
            texData[i*4+2] = 200;
            texData[i*4+3] = 255;
            break;
        case tileType::wall:
            texData[i*4]   = 0;
            texData[i*4+1] = 0;
            texData[i*4+2] = 0;
            texData[i*4+3] = 255;
            break;
        }
    }
    m_texture.setTextureData(texData, m_width, m_height); 
    delete texData;
}
