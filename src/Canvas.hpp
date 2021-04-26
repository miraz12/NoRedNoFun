#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class ShaderProgram;

class Canvas {
public:
    Canvas(ShaderProgram &ShaderProgram);
    ~Canvas();

    glm::mat4 getCanvasMatrix();

    void translate(float x, float y);
    void rotate(float rotation);
    void scale(float x, float y);
    void setTranslation(float x, float y);
    void setRotation(float rotation);
    void setScale(float x, float y);

    void setClearColor(float red, float green, float blue, float alpha);
    void clear();

    void applyCanvasMatrix();
private:
    float m_translation[2];
    float m_rotation;
    float m_scale[2];

    float m_color[4];

    glm::mat4 m_canvasMatrix;
    bool m_canvasMatrixNeedsUpdate;
    unsigned int m_canvasMatrixLoc;

    ShaderProgram& m_shaderProgram;
};
