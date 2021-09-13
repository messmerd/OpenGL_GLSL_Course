#pragma once

#include <string>
#include "glad/glad.h"

class Texture
{
public:
    Texture();

    void Bind();
    void Unbind();

    bool Load(const std::string& filename);
    void Unload();

private:
    GLuint m_Id;
};
