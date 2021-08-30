#pragma once

#include "glad/glad.h"
#include "Buffer.h"
#include "Shader.h"

class Renderable : public Buffer
{
public:
    Renderable()
        : Buffer()
    {}
    
    Renderable(const char* vertexName, const char* colorName)
        : Buffer(vertexName, colorName)
    {}

    virtual ~Renderable()
    {
        Destroy();
    };

    virtual void Render() = 0;
    virtual void Set(GLfloat* vertexData, GLsizeiptr vertexSize, GLfloat* colorData, GLsizeiptr colorSize) = 0;
};
