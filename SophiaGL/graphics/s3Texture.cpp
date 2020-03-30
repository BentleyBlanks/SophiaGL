#include <graphics/s3Texture.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

s3Texture::s3Texture(std::string path)
{
    // texture generation
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // map cpu data into miplevel 0 and generate mipmaps automatically
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        s3Log::error("Failed to load texture\n");
        bIsLoaded = false;
    }

    unsigned int format = (channels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    bIsLoaded = true;
}

s3Texture::~s3Texture()
{}

void s3Texture::begin()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void s3Texture::end()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int s3Texture::getWidth() const
{
	return width;
}

int s3Texture::getHeight() const
{
	return height;
}

int s3Texture::getChannels() const
{
	return channels;
}

bool s3Texture::isLoaded() const
{
	return bIsLoaded;
}

unsigned int s3Texture::getTexture() const
{
	return texture;
}
