#include "Quad.hpp"

#include <glad/glad.h>

#include "../ShaderPrograms/ShaderProgram.hpp"

Quad::Quad(ShaderProgram& shaderProgram):
    GraphicsObject(shaderProgram),
	m_spriteMap(0) {
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);
	setUseTexture(true);

	m_spriteMap.setNrOfSprites(1.0f, 1.0f);
	m_spriteMap.setCurrentSprite(0.0f, 0.0f);
}

Quad::~Quad() {

}

void Quad::update(float dt) {
	m_spriteMap.advanceSpriteBy(dt, 0.0f);
}

void Quad::draw() {
	m_spriteMap.bindSprite(p_shaderProgram.getUniformLocation("textureMatrix"));
    prepareDraw();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Using indices, call setIndexData().
	//glDrawArrays(GL_TRIANGLES, 0, 6); // Not using indices, don't call setIndexData().
}
