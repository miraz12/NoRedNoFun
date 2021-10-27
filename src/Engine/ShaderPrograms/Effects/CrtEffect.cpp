#include "CrtEffect.hpp"
#include <glad/glad.h>

CrtEffect::CrtEffect() : ShaderProgram("resources/Shaders/vertex_crt.glsl", "resources/Shaders/fragment_crt.glsl") {
	glUniform1i(m_uniformBindings["screenTexture"], 0);
}

void CrtEffect::setupVertexAttributePointers() {
   // Change if input layout changes in shaders
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
