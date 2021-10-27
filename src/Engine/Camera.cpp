#include "Camera.hpp"

#include <glad/glad.h>

Camera::Camera():
    m_viewMatrix(1.0f),
    m_matrixNeedsUpdate(false),
    m_position{0.0f, 0.0f},
    m_zoom(1.0f),
    m_rotation(0.0f),
    m_ratio(1.0f) {

}

Camera::~Camera() {

}

glm::mat4& Camera::getViewMatrix() {
    return m_viewMatrix;
}

void Camera::setPosition(float positionX, float positionY) {
    m_position.x = positionX;
    m_position.y = positionY;
    m_matrixNeedsUpdate = true;
}

void Camera::setZoom(float zoomAmount) {
    m_zoom = zoomAmount;
    m_matrixNeedsUpdate = true;
}

void Camera::setRotation(float rotation) {
    m_rotation = rotation;
    m_matrixNeedsUpdate = true;
}

void Camera::setAspectRatio(float ratio) {
    m_ratio = ratio;
    m_matrixNeedsUpdate = true;
}

void Camera::bindViewMatrix(unsigned int uniformLocation) {
    if (m_matrixNeedsUpdate) {
        m_viewMatrix = glm::mat4(1.0f);
        m_viewMatrix = glm::scale(m_viewMatrix, glm::vec3(m_zoom, m_zoom * m_ratio, 1.0f));
        m_viewMatrix = glm::rotate(m_viewMatrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(-m_position[0], -m_position[1], 0.0f));
        m_matrixNeedsUpdate = false;
    }

    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(m_viewMatrix));
}
