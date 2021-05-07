#pragma once

class Texture {
public:
    Texture(unsigned int textureIndex);
    virtual ~Texture();

    virtual void setTextureData(unsigned char* data, unsigned int width, unsigned int height);
    virtual void bind();
private:
    unsigned int m_texture;

	unsigned int m_textureIndex;

	unsigned char m_missingTextureData[16] = {
		255, 255, 255, 255, 0, 0, 0, 255,
		0, 0, 0, 255, 255, 255, 255, 255
	};
};
