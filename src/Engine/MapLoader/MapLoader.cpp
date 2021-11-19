#include "MapLoader.hpp"
#include <cstdlib>
#include <glad/glad.h>
#include <fstream>
#include <iostream>

MapLoader::MapLoader(ShaderProgram &shader, std::string mapName) : GraphicsObject(shader), m_texture(0), m_modelMatrix(1.0f), m_width(30), m_height(30) {

    loadMap(mapName);
    parseMap();
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

glm::mat4& MapLoader::getModelMatrix() {
	return m_modelMatrix;
}

void MapLoader::draw() {
    p_shaderProgram.use();
    bindVAO();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 1);
	glUniformMatrix4fv(p_shaderProgram.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    m_texture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool MapLoader::allowMovement(int x, int y) {
    if (x < 0 || static_cast<unsigned int>(x) >= m_width || y < 0 || static_cast<unsigned int>(y) >= m_height) {
        return false;
    }

    tileType tile = static_cast<tileType>(m_mapData[m_width * y + x]);
    if (tile == tileType::wall)
    {
        return false;
    }
    return true;
}

unsigned int MapLoader::getWidth() {
	return m_width;
}

unsigned int MapLoader::getHeight() {
	return m_height;
}

void MapLoader::parseMap() {
    unsigned char* texData;
    texData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * m_width * m_height * 4));
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
    free(texData);
}

void MapLoader::loadMap(std::string mapName) {
    std::ifstream file;
    file.open(mapName);
    if (file.is_open()) {
        int width;
        int height;
        file >> width;
        file >> height;
        m_mapData = static_cast<unsigned int*>(malloc(sizeof(unsigned int) * width * height));
        for (int i = 0; i < width * height; i++) {
            file >> m_mapData[i];
        }
        file.close(); 
        m_width = static_cast<unsigned int>(width);
        m_height = static_cast<unsigned int>(height);
    }
    else { 
        std::cerr << "Can't find input file " << mapName << std::endl;
    }
}
