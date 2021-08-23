#include "Shader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

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

GLuint Shader::BeginVAOBind()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    return vao;
}

void Shader::EndVAOBind()
{
    glBindVertexArray(0);
}

Uniform Shader::GetUniform(const char* name)
{
    Uniform u(m_ShaderProgramId, name);
    if (!u.IsValid())
        std::cout << "Shader variable '" << name << "' not found or not used." << std::endl;

    return u;
}

VertexAttribute Shader::GetVectorAttribute(const char* name)
{
    VertexAttribute va(m_ShaderProgramId, name);
    if (!va.IsValid())
        std::cout << "Shader variable '" << name << "' not found or not used." << std::endl;

    return va;
}

// Uniform variables

bool Uniform::Load(GLuint shaderProgramId, const char* name)
{
    m_Id = glGetUniformLocation(shaderProgramId, name);
    return m_Id != -1;
}

void Uniform::operator=(GLint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1i(m_Id, data);
}

void Uniform::operator=(GLuint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1ui(m_Id, data);
}

void Uniform::operator=(GLfloat data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1f(m_Id, data);
}

void Uniform::operator=(double data)
{
    *this = static_cast<GLfloat>(data);
}

void Uniform::operator=(std::initializer_list<GLint> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            glUniform2iv(m_Id, 1, data.begin());
            break;
        case 3:
            glUniform3iv(m_Id, 1, data.begin());
            break;
        case 4:
            glUniform4iv(m_Id, 1, data.begin());
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}

void Uniform::operator=(std::initializer_list<GLuint> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            glUniform2uiv(m_Id, 1, data.begin());
            break;
        case 3:
            glUniform3uiv(m_Id, 1, data.begin());
            break;
        case 4:
            glUniform4uiv(m_Id, 1, data.begin());
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}

void Uniform::operator=(std::initializer_list<GLfloat> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            glUniform2fv(m_Id, 1, data.begin());
            break;
        case 3:
            glUniform3fv(m_Id, 1, data.begin());
            break;
        case 4:
            glUniform4fv(m_Id, 1, data.begin());
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}

// Vertex Attributes - Vertex Buffer Objects (VBO) or Vertex Array Objects (VAO).
//      If using as VAOs, call Shader::BeginVAOBind() before calling VertexAttribute::Bind()'s and 
//      call Shader::EndVAOBind() afterwards.

bool VertexAttribute::Load(GLuint shaderProgramId, const char* name)
{
    m_Id = glGetAttribLocation(shaderProgramId, name);
    return m_Id != -1;
}

bool VertexAttribute::Bind(const void* data, GLsizeiptr size)
{
    m_VBO = 0;
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(m_Id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(m_Id);

    return true;
}

void VertexAttribute::Destroy()
{
    // Delete buffers then disable vertex attribute array
    glDeleteBuffers(1, &m_VBO);
    glDisableVertexAttribArray(m_Id);
}

void VertexAttribute::operator=(GLint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    //TODO
}

void VertexAttribute::operator=(GLuint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    //TODO
}

void VertexAttribute::operator=(GLfloat data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    //TODO
}

void VertexAttribute::operator=(double data)
{
    *this = static_cast<GLfloat>(data);
}

void VertexAttribute::operator=(std::initializer_list<GLint> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        case 4:
            //TODO
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}

void VertexAttribute::operator=(std::initializer_list<GLuint> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        case 4:
            //TODO
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}

void VertexAttribute::operator=(std::initializer_list<GLfloat> data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");

    switch (data.size())
    {
        case 2:
            //TODO
            break;
        case 3:
            //TODO
            break;
        case 4:
            //TODO
            break;
        default:
            throw std::invalid_argument("Wrong number of elements in initializer list");
    }
}
