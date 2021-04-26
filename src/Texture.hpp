#pragma once

class Texture {
public:
    Texture();
    ~Texture();

    bool getTextureEnabled();

    void enableTexture(bool use);
    void setTextureData(unsigned char* data, unsigned int width, unsigned int height);
    void bind();
private:
    unsigned int m_texture;
    bool m_useTexture;
};
