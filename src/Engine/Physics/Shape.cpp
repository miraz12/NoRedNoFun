#include "Shape.hpp"

Shape::Shape() 
    : m_verticesNeedsUpdate(false), 
    m_normalsNeedsUpdate(false),
    m_transformMatrix(1.0f) {

}

Shape::~Shape() {

}

void Shape::addVertex(glm::vec2 vertex) {
    m_originalVertices.emplace_back(vertex);
    m_verticesNeedsUpdate = true;
}

void Shape::addNormal(glm::vec2 normal) {
    m_originalNormals.emplace_back(normal);
    m_normalsNeedsUpdate = true;
}

void Shape::clearVertices() {
    m_originalVertices.clear();
    m_verticesNeedsUpdate = true;
}

void Shape::clearNormals() {
    m_originalNormals.clear();
    m_normalsNeedsUpdate = true;
}

void Shape::setTransformMatrix(const glm::mat4 &matrix) {
    m_transformMatrix = matrix;
    m_verticesNeedsUpdate = true;
    m_normalsNeedsUpdate = true;
}

const std::vector<glm::vec2>& Shape::getTransformedVertices() {
    if (m_verticesNeedsUpdate) {
        m_transformedVertices.clear();
        for (size_t i = 0; i < m_originalVertices.size(); i++) {
            m_transformedVertices.emplace_back(m_transformMatrix * glm::vec4(m_originalVertices[i], 0.0f, 1.0f));
        }
        m_verticesNeedsUpdate = false;
    }
    return m_transformedVertices;
}

const std::vector<glm::vec2>& Shape::getTransformedNormals() {
    if (m_normalsNeedsUpdate) {
        m_transformedNormals.clear();
        for (size_t i = 0; i < m_originalNormals.size(); i++) {
            m_transformedNormals.emplace_back(glm::mat3(glm::transpose(glm::inverse(m_transformMatrix))) * glm::vec3(m_originalNormals[i], 0.0f));
            m_transformedNormals.back() = glm::normalize(m_transformedNormals.back());
        }
        m_normalsNeedsUpdate = false;
    }
    return m_transformedNormals;
}