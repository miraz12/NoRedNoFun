#pragma once

#include <vector>

#include "GraphicsObject.hpp"

class ShaderProgram;

class Pen : public GraphicsObject {
public:
    Pen(ShaderProgram &shaderProgram);
    virtual ~Pen();

    void setCurrentColor(glm::vec3 color);
    void addStop(glm::vec3 position);

    virtual void draw();
private:
    std::vector<float> m_vertices;
    glm::vec3 m_currentColor;
};
