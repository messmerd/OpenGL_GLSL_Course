#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader()
{
    m_ShaderProgramId = 0;
    m_VertexShaderId = 0;
    m_FragmentShaderId = 0;
}

Shader* Shader::Instance()
{
    // First call will create shader object and all subsequent calls will just return shader pointer
    static Shader* shader = new Shader;
    return shader;
}

bool Shader::CreateProgram()
{
    m_ShaderProgramId = glCreateProgram();

    if (m_ShaderProgramId == 0)
    {
        std::cout << "Error creating shader program" << std::endl;
        return false;
    }
    
    return true;
}

bool Shader::CreateShaders()
{
    m_VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (m_VertexShaderId == 0)
    {
        std::cout << "Error creating vertex shader object" << std::endl;
        return false;
    }

    m_FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_FragmentShaderId == 0)
    {
        std::cout << "Error creating fragment shader object" << std::endl;
        return false;
    }

    return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::fstream file;
    std::string sourceCode, line;
    const GLuint shaderId = shaderType == ShaderType::VERTEX_SHADER ? m_VertexShaderId : m_FragmentShaderId;

    file.open(filename);
    if (!file)
    {
        std::cout << "Error reading shader file: " << filename << std::endl;
        return false;
    }

    while (!file.eof())
    {
        std::getline(file, line);
        sourceCode += line + "\n";
    }

    file.close();

    const auto* finalSourceCode = static_cast<const GLchar*>(sourceCode.c_str());
    glShaderSource(shaderId, 1, &finalSourceCode, nullptr); // Shader Id, 1 shader, shader source code, length

    glCompileShader(shaderId);

    GLint errorCode;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &errorCode);

    if (errorCode == GL_TRUE)
    {
        std::cout << "Shader compilation successful" << std::endl;
    }
    else
    {
        const GLsizei bufferSize = 1000;
        GLsizei bufferSizeReturn = bufferSize;
        GLchar errorMessage[bufferSize];

        glGetShaderInfoLog(shaderId, bufferSize, &bufferSizeReturn, errorMessage);
        std::cout << "Error compiling shader:" << std::endl << errorMessage << std::endl;
        return false;
    }

    return true;
}

void Shader::AttachShaders()
{
    glAttachShader(m_ShaderProgramId, m_VertexShaderId);
    glAttachShader(m_ShaderProgramId, m_FragmentShaderId);
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_ShaderProgramId);

    glUseProgram(m_ShaderProgramId);

    GLint errorCode;
    glGetProgramiv(m_ShaderProgramId, GL_LINK_STATUS, &errorCode);

    if (errorCode == GL_TRUE)
    {
        std::cout << "Shader linking successful" << std::endl;
    }
    else
    {
        const GLsizei bufferSize = 1000;
        GLsizei bufferSizeReturn = bufferSize;
        GLchar errorMessage[bufferSize];

        glGetProgramInfoLog(m_ShaderProgramId, bufferSize, &bufferSizeReturn, errorMessage);
        std::cout << "Error linking shader:" << std::endl << errorMessage << std::endl;
        return false;
    }

    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_ShaderProgramId, m_VertexShaderId);
    glDetachShader(m_ShaderProgramId, m_FragmentShaderId);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_VertexShaderId);
    glDeleteShader(m_FragmentShaderId);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_ShaderProgramId);
}
