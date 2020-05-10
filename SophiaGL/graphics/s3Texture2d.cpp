#include <graphics/s3Texture2d.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

s3Texture2d s3Texture2d::blackTexture;
s3Texture2d s3Texture2d::whiteTexture;
s3Texture2d s3Texture2d::grayTexture;

//--! ref: https://docs.unity3d.com/2017.4/Documentation/ScriptReference/Texture2D.html
bool s3Texture2d::load(const char* path)
{
    if (!path)
    {
        bIsLoaded = false;
        return false;
    }

    // texture generation
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // map cpu data into miplevel 0 and generate mipmaps automatically
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data)
    {
        s3Log::error("Failed to load texture\n");
        bIsLoaded = false;
        return false;
    }

    unsigned int format = (channels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    bIsLoaded = true;
    return true;
}