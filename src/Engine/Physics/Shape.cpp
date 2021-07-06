#include "Shape.hpp"

Shape::Shape() 
: m_centerPosition(0.0f){

}

Shape::~Shape() {

}

void Shape::addVertex(glm::vec2 vertex) {
    m_vertices.emplace_back(vertex);
}

void Shape::addNormal(glm::vec2 normal) {
    m_normals.emplace_back(normal);
}

void Shape::setPosition(glm::vec2 position) {
    m_centerPosition = position;
}

const std::vector<glm::vec2>& Shape::getVertices() const {
    return m_vertices;
}

const std::vector<glm::vec2>& Shape::getNormals() const {
    return m_normals;
}

void Shape::moveShape(glm::vec2 newPos) {
    glm::vec2 deltaPosition = newPos - m_centerPosition;
    m_centerPosition = newPos;

    for (auto& vec : m_vertices) {
        vec.x += deltaPosition.x;
        vec.y += deltaPosition.y;
    }
}
