#include "Shader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

Shader::Shader()
{
    m_IsInitialized = false;
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

bool Shader::Initialize(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
    // Create shader program and shader objects
    if (!CreateProgram() || !CreateShaders())
        return false;

    // Compile vertex shader
    if (!CompileShaders(vertexShaderFilename, Shader::ShaderType::VERTEX_SHADER))
        return false;

    // Compile fragment shader
    if (!CompileShaders(fragmentShaderFilename, Shader::ShaderType::FRAGMENT_SHADER))
        return false;

    // Attach shaders to shader program
    AttachShaders();

    // Link shaders to shader program
    if (!LinkProgram())
        return false;

    m_IsInitialized = true;
    return true;
}

void Shader::Destroy()
{
    DetachShaders();
    DestroyProgram();
    m_IsInitialized = false;
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
        std::cout << "Shader compilation successful (" << filename << ")" << std::endl;
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

// Uniform variables

bool Uniform::Load(GLuint shaderProgramId, const char* name)
{
    if (shaderProgramId == 0)
        return false;

    m_Id = glGetUniformLocation(shaderProgramId, name);
    if (m_Id == -1)
        std::cout << "Error: Uniform::m_Id == 0" << std::endl;

    return m_Id != -1;
}

void Uniform::Set(GLint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1i(m_Id, data);
}

void Uniform::Set(GLuint data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1ui(m_Id, data);
}

void Uniform::Set(GLfloat data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniform1f(m_Id, data);
}

void Uniform::Set(double data)
{
    Set(static_cast<GLfloat>(data));
}

void Uniform::Set(std::initializer_list<GLint> data)
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

void Uniform::Set(std::initializer_list<GLuint> data)
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

void Uniform::Set(std::initializer_list<GLfloat> data)
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

void Uniform::Set(const glm::mat4& data)
{
    if (m_Id == -1)
        throw std::invalid_argument("Invalid uniform id");
    
    glUniformMatrix4fv(m_Id, 1, GL_FALSE, &data[0][0]);
}

// Vertex Attributes - Vertex Buffer Objects (VBO) or Vertex Array Objects (VAO).
//      If using as VAO, need to generate and bind VAO before calling VertexAttribute::Bind()'s and 
//      then unbind VAO afterwards.

bool VertexAttribute::Load(const char* name)
{
    return Load(Shader::Instance()->GetShaderProgramId(), name);
}

bool VertexAttribute::Load(GLuint shaderProgramId, const char* name)
{
    if (shaderProgramId == 0)
        return false;

    m_Id = glGetAttribLocation(shaderProgramId, name);
    if (m_Id == -1)
        std::cout << "Error: VertexAttribute::m_Id == 0" << std::endl;

    m_VBO = 0;
    glGenBuffers(1, &m_VBO);

    return m_Id != -1;
}

void VertexAttribute::Set(GLfloat* data, GLsizeiptr size, FillType fillType)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, fillType);
}

bool VertexAttribute::Link(ComponentType componentType, DataType dataType)
{
    // Tell it which VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(m_Id, componentType, dataType, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(m_Id);

    return true;
}

void VertexAttribute::Destroy()
{
    // Delete buffers then disable vertex attribute array
    glDeleteBuffers(1, &m_VBO);
    //glDisableVertexAttribArray(m_Id);
}

void GetError(const char* context)
{
    GLenum loop_error = glGetError();
    while (loop_error != GL_NO_ERROR)
    {
        std::cout << "Error! Context: " << context << ": ";
        switch (loop_error)
        {
        case GL_NO_ERROR: std::cout << "GL_NO_ERROR" << std::endl; break;
        case GL_INVALID_ENUM: std::cout << "GL_INVALID_ENUM" << std::endl; break;
        case GL_INVALID_VALUE: std::cout << "GL_INVALID_VALUE" << std::endl; break;
        case GL_INVALID_OPERATION: std::cout << "GL_INVALID_OPERATION" << std::endl; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
        case GL_OUT_OF_MEMORY: std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
        }
        loop_error = glGetError();
    }
}
