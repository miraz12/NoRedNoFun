#include "Texture.hpp"

#include <glad/glad.h>

Texture::Texture(unsigned int textureIndex) {
	m_textureIndex = textureIndex;

    // Generate texture
    glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0 + m_textureIndex);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_missingTextureData);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {

}

void Texture::setTextureData(unsigned char* data, unsigned int width, unsigned int height) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0 + m_textureIndex);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
