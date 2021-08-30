#include "Quad.h"

Quad::Quad(const char* vertexName, const char* colorName)
    : Renderable(vertexName, colorName)
{
    Create(6);
}

void Quad::Render() const
{
    Buffer::Render(Buffer::TRIANGLES);
}

void Quad::Set(GLfloat* vertexData, GLsizeiptr vertexSize, GLfloat* colorData, GLsizeiptr colorSize)
{
    FillVBO(Buffer::VERTEX_BUFFER, vertexData, vertexSize, VertexAttribute::SINGLE);
    FillVBO(Buffer::COLOR_BUFFER, colorData, colorSize, VertexAttribute::SINGLE);

    Link(Buffer::VERTEX_BUFFER, VertexAttribute::XYZ, VertexAttribute::FLOAT);
    Link(Buffer::COLOR_BUFFER, VertexAttribute::RGB, VertexAttribute::FLOAT);
}

void Quad::Set()
{
    // Data that represents vertices for quad
    GLfloat vertices[] = {  -1.0f,  +1.0f,  0.0f,
                            +1.0f,  +1.0f,  0.0f,
                            -1.0f,  -1.0f,  0.0f, // Triangle 1

                            -1.0f,  -1.0f,  0.0f,
                            +1.0f,  +1.0f,  0.0f,
                            +1.0f,  -1.0f,  0.0f }; // Triangle 2

    // Data that represents colors for quad
    GLfloat colors[] = {    0.0f,   0.0f,   1.0f,
                            0.0f,   0.0f,   1.0f,
                            1.0f,   1.0f,   1.0f, // Triangle 1

                            1.0f,   1.0f,   1.0f,
                            0.0f,   0.0f,   1.0f,
                            1.0f,   1.0f,   1.0f }; // Triangle 2

    Set(vertices, sizeof(vertices), colors, sizeof(colors));
}
