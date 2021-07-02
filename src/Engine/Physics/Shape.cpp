#include "Shape.hpp"

Shape::Shape() {

}

Shape::~Shape() {

}

void Shape::addVertex(glm::vec2 vertex) {
    m_vertices.emplace_back(vertex);
}

void Shape::addNormal(glm::vec2 normal) {
    m_normals.emplace_back(normal);
}

const std::vector<glm::vec2>& Shape::getVertices() const {
    return m_vertices;
}

const std::vector<glm::vec2>& Shape::getNormals() const {
    return m_normals;
}
