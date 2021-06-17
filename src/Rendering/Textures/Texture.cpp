#include "Texture.hpp"

#include <iostream>
#include <glad/glad.h>

Texture::Texture(unsigned int textureIndex) {
	m_textureIndex = textureIndex;

    // Generate texture
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	m_width = 2;
	m_height = 2;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_missingTextureData);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

unsigned int Texture::getWidth() {
	return m_width;
}

unsigned int Texture::getHeight() {
	return m_height;
}

void Texture::setTextureData(unsigned char* data, unsigned int width, unsigned int height) {
	m_width = width;
	m_height = height;
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::updateTextureSubData(unsigned char* data, unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height) {
	if (xOffset + width <= m_width && yOffset + height <= m_height) {
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		return true;
	}
	
	std::cout << "Tried to update texture sub data outside of bounds\n";
	return false;
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0 + m_textureIndex);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
