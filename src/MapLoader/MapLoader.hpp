#pragma once
#include "../Objects/Quad.hpp"
#include "../Textures/Texture.hpp"
#include "../Objects/GraphicsObject.hpp"
#include "../ShaderPrograms/SimpleShaderProgram.hpp"

#include <glm/glm.hpp>

class MapLoader : protected GraphicsObject {
public:
    MapLoader(ShaderProgram &shader);
    ~MapLoader();
    void draw();
private:

    unsigned int m_VBO;
    Quad m_quad;
    Texture m_texture;
    SimpleShaderProgram m_shader;
    glm::mat4 m_modelMat;
    glm::mat4 m_textureMat;


    unsigned char m_mapData [10*10] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    float m_vertices[20] = {
        //Position             Texture coords
        -0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,    0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,     1.0f, 0.0f,
    };
    unsigned int m_indices[6] = {
        0, 1, 2,
        2, 1, 3,
    };
   
};
