#pragma once

#include "glad/glad.h"
#include "Shader.h"

class Buffer
{
public:
    enum VBOType { VERTEX_BUFFER, COLOR_BUFFER };
    enum DrawType { POINTS = GL_POINTS, TRIANGLES = GL_TRIANGLES, LINES = GL_LINES }; // Can add support for others later
    typedef VertexAttribute::ComponentType ComponentType;
    typedef VertexAttribute::DataType DataType;
    typedef VertexAttribute::FillType FillType;

protected:
    Buffer();
    Buffer(const char* vertexName, const char* colorName);

    void Create(GLuint totalVertices);
    void Create(const char* vertexName, const char* colorName, GLuint totalVertices);
    void Destroy();

    void FillVBO(VBOType vboType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType);
    void FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType);

    void Link(VBOType vboType, ComponentType componentType, DataType dataType);

    void Render(DrawType drawType) const;

private:
    GLuint m_VAO;
    GLuint m_TotalVertices;

    VertexAttribute m_VertexAttribute;
    VertexAttribute m_ColorAttribute;
};

