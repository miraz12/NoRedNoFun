#pragma once
#include "../Objects/Quad.hpp"
#include "../Textures/Texture.hpp"
#include "../Objects/GraphicsObject.hpp"
#include "../ShaderPrograms/SimpleShaderProgram.hpp"

#include <glm/glm.hpp>

class MapLoader : protected GraphicsObject {
public:
    MapLoader(ShaderProgram &shader, std::string mapName);
    ~MapLoader();
    void draw();
private:

    void loadMap(std::string mapName);
    void parseMap();
    Texture m_texture;
    
    unsigned int m_width;
    unsigned int m_height;

    enum tileType {
        ground,
        wall
    };

    unsigned int* m_mapData;

    float m_vertices[36] = {
        //Position              Color                       Texture coords
        -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 1.0f,
        1.0f, -1.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,
        1.0f,  1.0f, 0.0f,      1.0f, 0.0f, 1.0f, 1.0f,     1.0f, 0.0f
    };
    unsigned int m_indices[6] = {
        0, 1, 2,
        2, 1, 3,
    };
   
};
