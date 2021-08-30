#pragma once

#include "Renderable.h"

class Quad : public Renderable
{
public:
    Quad(const char* vertexName, const char* colorName);

    void Render() const override;
    void Set(GLfloat* vertexData, GLsizeiptr vertexSize, GLfloat* colorData, GLsizeiptr colorSize) override;
    
    void Set(); // Default set - temporary method for testing purposes
};
