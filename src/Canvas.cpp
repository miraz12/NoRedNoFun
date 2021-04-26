#include "Canvas.hpp"
#include "ShaderProgram.hpp"

#include <glad/glad.h>

Canvas::Canvas(ShaderProgram &shaderProgram) :
    m_translation{0.0f, 0.0f},
    m_rotation(0.f),
    m_scale{1.f, 1.f},
    m_color{0.0f, 0.0f, 0.0f, 1.0f},
    m_canvasMatrix(1.0f),
    m_canvasMatrixNeedsUpdate(false),
    m_shaderProgram(shaderProgram) {
    setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Canvas::~Canvas() {

}

glm::mat4 Canvas::getCanvasMatrix() {
    if (m_canvasMatrixNeedsUpdate) {
        m_canvasMatrix = glm::mat4(1.0f);

        m_canvasMatrix = glm::translate(m_canvasMatrix, glm::vec3(m_translation[0], m_translation[1], 0.f));
        m_canvasMatrix = glm::rotate(m_canvasMatrix, m_rotation, glm::vec3(0.f, 0.f, 1.0f));
        m_canvasMatrix = glm::scale(m_canvasMatrix, glm::vec3(m_scale[0], m_scale[1], 1.0f));

        m_canvasMatrixNeedsUpdate = false;
    }

    return m_canvasMatrix;
}

void Canvas::translate(float x, float y) {
    m_translation[0] += x;
    m_translation[1] += y;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::rotate(float rotation) {
    m_rotation += rotation;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::scale(float x, float y) {
    m_scale[0] += x;
    m_scale[1] += y;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::setTranslation(float x, float y) {
    m_translation[0] = x;
    m_translation[1] = y;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::setRotation(float rotation) {
    m_rotation = rotation;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::setScale(float x, float y) {
    m_scale[0] = x;
    m_scale[1] = y;
    m_canvasMatrixNeedsUpdate = true;
}

void Canvas::setClearColor(float red, float green, float blue, float alpha) {
    m_color[0] = red;
    m_color[1] = green;
    m_color[2] = blue;
    m_color[3] = alpha;
    glClearColor(m_color[0], m_color[1], m_color[2], m_color[3]);
}

void Canvas::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Canvas::applyCanvasMatrix() {
    if (m_shaderProgram.getUniformLocation("canvasMatrix", m_canvasMatrixLoc)) {
        glUniformMatrix4fv(m_canvasMatrixLoc, 1, GL_FALSE, glm::value_ptr(getCanvasMatrix()));
    }
}
