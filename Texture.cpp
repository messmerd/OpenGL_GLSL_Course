#include "Texture.h"

#include <SDL_image.h>
#include <iostream>

Texture::Texture()
{
    m_Id = 0;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::Load(const std::string& filename)
{
    SDL_Surface* textureData = IMG_Load(filename.c_str());
    if (!textureData)
    {
        std::cout << "Error loading texture." << std::endl;
    }

    const GLsizei width = textureData->w, height = textureData->h;
    const Uint8* pixels = (Uint8*)textureData->pixels;
    const Uint8 depth = textureData->format->BitsPerPixel; // RGB (3) or RGBA (4)

    const GLint format = depth == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &m_Id);

    Bind();

        // Filter setting so that fragment shader knows how to deal with the images properly:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Magnification
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Minification

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

    Unbind();

    SDL_FreeSurface(textureData);

    return true;
}

void Texture::Unload()
{
    glDeleteTextures(1, &m_Id);
}
