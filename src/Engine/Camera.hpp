#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    glm::mat4& getViewMatrix();

    void setPosition(float positionX, float positionY); // Set position of camera (2D)
    void setZoom(float zoomAmount);
    void setRotation(float rotation); // Set rotation clockwise

    glm::vec2& getPosition() { return m_position; };

    void setAspectRatio(float ratio);
    void bindViewMatrix(unsigned int uniformLocation);
private:
    glm::mat4 m_viewMatrix;
    bool m_matrixNeedsUpdate;

    glm::vec2 m_position;
    float m_zoom;
    float m_rotation;
    float m_ratio;
};
