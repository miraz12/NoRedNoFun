#include "InstancedQuadManager.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>


InstancedQuadManager::InstancedQuadManager(ShaderProgram &shaderProgram):
	m_shaderProgram(shaderProgram) {
	
	glGenBuffers(1, &m_instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

InstancedQuadManager::~InstancedQuadManager() {

}