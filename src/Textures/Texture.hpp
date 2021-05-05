#pragma once

class Texture {
public:
    Texture(unsigned int textureIndex);
    virtual ~Texture();

    virtual bool getTextureEnabled();

    virtual void enableTexture(bool use);
    virtual void setTextureData(unsigned char* data, unsigned int width, unsigned int height);
    virtual void bind();
private:
    unsigned int m_texture;
    bool m_useTexture;

	unsigned int m_textureIndex;
};
