#include "Quad.hpp"

#include <glad/glad.h>
#include <cstdlib>

#include "../ShaderPrograms/ShaderProgram.hpp"

Quad::Quad(ShaderProgram& shaderProgram):
    GraphicsObject(shaderProgram),
    m_useTexture(true),
    m_modelMatrix(1.0f),
	m_spriteMap(0),
	m_updateTextureTimer(0.5f) {
    setVertexData(sizeof(m_vertices), m_vertices);
    setIndexData(sizeof(m_indices), m_indices);

	m_spriteMap.setNrOfSprites(0.2f, 0.2f);
	m_spriteMap.setCurrentSprite(0.0f, 0.0f);
}

Quad::~Quad() {

}

void Quad::update(float dt) {
	m_spriteMap.advanceSpriteBy(dt, 0.2f * dt);

	if (m_updateTextureTimer <= 0.0f) {
		unsigned char updateTextureData[4] = {
		(unsigned char) (rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), 255
		};
		m_spriteMap.updateTextureSubData(updateTextureData, 0, 0, 1, 1);
		m_updateTextureTimer += 0.5f;
	}
	

	m_updateTextureTimer -= dt;
}

void Quad::draw() {
    bindVAO();
	m_spriteMap.bindSprite();
    glUniformMatrix4fv(p_shaderProgram.getUniformLocation("textureMatrix"), 1, GL_FALSE, glm::value_ptr(m_spriteMap.getTextureMatrix()));
    glUniformMatrix4fv(p_shaderProgram.getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix)); // Bind model matrix
    glUniform1i(p_shaderProgram.getUniformLocation("useTexture"), m_useTexture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Using indices, call setIndexData().
	//glDrawArrays(GL_TRIANGLES, 0, 6); // Not using indices, don't call setIndexData().
}
