#pragma once

#include <string>
#include "glad/glad.h"
#include "glm/glm.hpp"

void GetError(const char* context); // For debugging

class Uniform; // Forward definition
class VertexAttribute; // Forward definition

class Shader
{
public:
    enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };

public:
    static Shader* Instance();

    // Create shader program, create/compile/attach shaders, and link shaders to program
    bool Initialize(const char* vertexShaderFilename, const char* fragmentShaderFilename);

    // Detach shaders and destroy shader program
    void Destroy();

    bool IsInitialized() { return m_IsInitialized; }
    GLuint GetShaderProgramId() { return m_ShaderProgramId; }
    
private:
    Shader();
    Shader(const Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    bool CreateProgram();
    bool CreateShaders();

    bool CompileShaders(const std::string& filename, ShaderType shaderType);
    void AttachShaders();
    bool LinkProgram();

    void DetachShaders();
    void DestroyShaders();
    void DestroyProgram();

private:
    bool m_IsInitialized;

    GLuint m_ShaderProgramId;
    GLuint m_VertexShaderId;
    GLuint m_FragmentShaderId;
};

class ShaderVariable
{
friend class Shader;

protected:
    ShaderVariable() { m_Id = -1; }

    virtual bool Load(GLuint shaderProgramId, const char* name) = 0;

public:
    bool IsValid() const { return m_Id != -1; }
    
protected:
    GLint m_Id;
};

class Uniform : public ShaderVariable
{
friend class Shader;

public:
    Uniform() : ShaderVariable() {};
    Uniform(const char* name)
    {
        Load(Shader::Instance()->GetShaderProgramId(), name);
    }

private:
    //Uniform(const Uniform& u) = delete; // Prevent copy constructor from being used
    Uniform(GLuint shaderProgramId, const char* name)
    {
        Load(shaderProgramId, name);
    }

public:
    bool Load(GLuint shaderProgramId, const char* name);

    void Set(GLint data);
    void Set(GLuint data);
    void Set(GLfloat data);
    void Set(double data);

    void Set(std::initializer_list<GLint> data);
    void Set(std::initializer_list<GLuint> data);
    void Set(std::initializer_list<GLfloat> data);

    void Set(const glm::mat4& data);
};

class VertexAttribute : public ShaderVariable
{
friend class Shader;

public:
    enum ComponentType { XY = 2, XYZ = 3, RGB = 3, RGBA = 4, UV = 2 };
    enum DataType { INT = GL_INT, FLOAT = GL_FLOAT, UNSIGNED_INT = GL_UNSIGNED_INT };
    enum FillType { SINGLE = GL_STATIC_DRAW, MULTIPLE = GL_DYNAMIC_DRAW };

    VertexAttribute() : ShaderVariable() { m_VBO = 0; }
    VertexAttribute(const char* name)
    {
        Load(Shader::Instance()->GetShaderProgramId(), name);
    }

private:
    //VertexAttribute(const VertexAttribute& va) = delete; // Prevent copy constructor from being used
    VertexAttribute(GLuint shaderProgramId, const char* name)
    {
        Load(shaderProgramId, name);
    }

public:
    bool Load(const char* name);
    bool Load(GLuint shaderProgramId, const char* name);
    void Set(GLfloat* data, GLsizeiptr size, FillType fillType);
    bool Link(ComponentType componentType, DataType dataType);

    void Destroy();

private:
    GLuint m_VBO;
};
