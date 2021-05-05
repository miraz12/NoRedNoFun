#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    void setPosition(float positionX, float positionY); // Set position of camera (2D)
    void setZoom(float zoomAmount);
    void setRotation(float rotation); // Set rotation clockwise

    void bindViewMatrix(unsigned int uniformLocation);
private:
    glm::mat4 m_viewMatrix;
    bool m_matrixNeedsUpdate;

    float m_position[2];
    float m_zoom;
    float m_rotation;
};
