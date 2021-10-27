#include "QuadShaderProgram.hpp"
#include <glad/glad.h>



QuadShaderProgram::QuadShaderProgram() : ShaderProgram("resources/Shaders/vertex_quad.glsl", "resources/Shaders/fragment_quad.glsl") {
	glUniform1i(m_uniformBindings["screenTexture"], 0);
}

void QuadShaderProgram::setupVertexAttributePointers() {
    // Change if input layout changes in shaders
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}