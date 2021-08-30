#include "Buffer.h"
#include <iostream>

Buffer::Buffer()
    : m_VertexAttribute(), m_ColorAttribute()
{
    m_VAO = 0;
    m_TotalVertices = 0;
}

Buffer::Buffer(const char* vertexName, const char* colorName)
    : m_VertexAttribute(vertexName), m_ColorAttribute(colorName)
{
    m_VAO = 0;

    if (!Shader::Instance()->IsInitialized())
        std::cout << "Cannot create quad: Shader program is uninitialized." << std::endl;
    else
    {
        if (!m_VertexAttribute.IsValid())
        std::cout << "Shader vertex variable '" << vertexName << "' not found or not used." << std::endl;

        if (!m_ColorAttribute.IsValid())
            std::cout << "Shader color variable '" << colorName << "' not found or not used." << std::endl;
    }

    m_TotalVertices = 0;
}

void Buffer::Create(GLuint totalVertices)
{
    glGenVertexArrays(1, &m_VAO);

    m_TotalVertices = totalVertices;
}

void Buffer::Create(const char* vertexName, const char* colorName, GLuint totalVertices)
{
    glGenVertexArrays(1, &m_VAO);

    m_VertexAttribute.Load(vertexName); 
    m_ColorAttribute.Load(colorName);

    if (!Shader::Instance()->IsInitialized())
        std::cout << "Cannot create quad: Shader program is uninitialized." << std::endl;
    else
    {
        if (!m_VertexAttribute.IsValid())
        std::cout << "Shader vertex variable '" << vertexName << "' not found or not used." << std::endl;

        if (!m_ColorAttribute.IsValid())
            std::cout << "Shader color variable '" << colorName << "' not found or not used." << std::endl;
    }

    m_TotalVertices = totalVertices;
}

void Buffer::Destroy()
{
    m_VertexAttribute.Destroy();
    m_ColorAttribute.Destroy();
    glDeleteVertexArrays(1, &m_VAO);
}

void Buffer::FillVBO(VBOType vboType, GLfloat* data, GLsizeiptr bufferSize, FillType fillType)
{
    glBindVertexArray(m_VAO);

        VertexAttribute& attribute = vboType == VERTEX_BUFFER ? m_VertexAttribute : m_ColorAttribute;
        attribute.Set(data, bufferSize, fillType);

    glBindVertexArray(0);

}

void Buffer::FillEBO(GLuint* data, GLsizeiptr bufferSize, FillType fillType)
{

}

void Buffer::Link(VBOType vboType, ComponentType componentType, DataType dataType)
{
    glBindVertexArray(m_VAO);

        VertexAttribute& attribute = vboType == VERTEX_BUFFER ? m_VertexAttribute : m_ColorAttribute;
        attribute.Link(componentType, dataType);

    glBindVertexArray(0);
}

void Buffer::Render(DrawType drawType)
{
    glBindVertexArray(m_VAO);

        glDrawArrays(drawType, 0, m_TotalVertices);

    glBindVertexArray(0);
}
