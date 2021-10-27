#pragma once

#include <vector>

#include "GraphicsObject.hpp"

class LowPolyLiquid : public GraphicsObject {
public:
    LowPolyLiquid(ShaderProgram &shaderProgram);
    virtual ~LowPolyLiquid();

    void setCurrentColor(glm::vec4 color);
    void addStop(glm::vec3 position);

    virtual void draw();
private:
    std::vector<float> m_vertices;
    glm::vec4 m_currentColor;
};
