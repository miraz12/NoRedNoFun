#include "MapLoader.hpp"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

MapLoader::MapLoader(ShaderProgram &shader) : GraphicsObject(shader), m_texture(0), m_width(30), m_height(30) { 

    loadMap("resources/Maps/simple.map");
    parseMap();
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
}

MapLoader::~MapLoader() {
    delete m_mapData;
}

void MapLoader::draw() {
    p_shaderProgram.use();
    bindVAO();
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), 1);
    m_texture.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void MapLoader::parseMap() {
    unsigned char* texData;
    texData = (unsigned char*) malloc(sizeof(unsigned char) * m_width * m_height * 4);
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
