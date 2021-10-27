#pragma once

#include <string>

class Texture {
public:
    Texture(unsigned int textureIndex);
    virtual ~Texture();

	virtual unsigned int getWidth();
	virtual unsigned int getHeight();

    virtual void setTextureData(unsigned char* data, unsigned int width, unsigned int height);
	virtual bool updateTextureSubData(unsigned char* data, unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height);
    virtual void bind();
	virtual void loadFromFile(std::string path);
	virtual void setTexParameters(unsigned int, unsigned int);
private:
    unsigned int m_texture;
	unsigned int m_textureIndex;

	unsigned int m_width;
	unsigned int m_height;

	unsigned char m_missingTextureData[24] = {
		255, 255, 255, 255, 0, 0, 0, 255,
		0, 0, 0, 255, 255, 255, 255, 255,
		0, 255, 0, 255, 255, 0, 0, 255
	};
};
