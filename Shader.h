#pragma once

#include <string>
#include "glad/glad.h"

class Uniform; // Forward definition
class VertexAttribute; // Forward definition

class Shader
{
public:
    enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };

public:
    static Shader* Instance();

public:
    bool CreateProgram();
    bool CreateShaders();

    bool CompileShaders(const std::string& filename, ShaderType shaderType);
    void AttachShaders();
    bool LinkProgram();

    void DetachShaders();
    void DestroyShaders();
    void DestroyProgram();

    GLuint GetShaderProgramId() { return m_ShaderProgramId; }

    GLuint BeginVAOBind();
    void EndVAOBind();

    Uniform GetUniform(const char* name);
    VertexAttribute GetVectorAttribute(const char* name);

private:
    Shader();
    Shader(const Shader&);
    Shader& operator=(Shader&);

    bool LoadUniform(const char* uniformName);

private:
    GLuint m_ShaderProgramId;
    GLuint m_VertexShaderId;
    GLuint m_FragmentShaderId;
};

class ShaderVariable
{
friend class Shader;
protected:
    ShaderVariable() { m_Id = -1; }

protected:
    virtual bool Load(GLuint shaderProgramId, const char* name) = 0;
    bool IsValid() const { return m_Id != -1; }

    virtual void operator=(GLint data) = 0;
    virtual void operator=(GLuint data) = 0;
    virtual void operator=(GLfloat data) = 0;
    virtual void operator=(double data) = 0;

    virtual void operator=(std::initializer_list<GLint> data) = 0;
    virtual void operator=(std::initializer_list<GLuint> data) = 0;
    virtual void operator=(std::initializer_list<GLfloat> data) = 0;

protected:
    GLint m_Id;
};

class Uniform : public ShaderVariable
{
friend class Shader;

private:
    //Uniform(const Uniform& u); // Prevent copy constructor from being used
    Uniform() : ShaderVariable() {};
    Uniform(GLuint shaderProgramId, const char* name)
    {
        Load(shaderProgramId, name);
    }

public:
    bool Load(GLuint shaderProgramId, const char* name);

    void operator=(GLint data);
    void operator=(GLuint data);
    void operator=(GLfloat data);
    void operator=(double data);

    void operator=(std::initializer_list<GLint> data);
    void operator=(std::initializer_list<GLuint> data);
    void operator=(std::initializer_list<GLfloat> data);
};

class VertexAttribute : public ShaderVariable
{
friend class Shader;

private:
    //VertexAttribute(const VertexAttribute& va); // Prevent copy constructor from being used
    VertexAttribute() : ShaderVariable() { m_VBO = 0; }
    VertexAttribute(GLuint shaderProgramId, const char* name)
    {
        Load(shaderProgramId, name);
    }

public:
    bool Load(GLuint shaderProgramId, const char* name);
    bool Bind(const void* data, GLsizeiptr size);

    void Destroy();

    void operator=(GLint data);
    void operator=(GLuint data);
    void operator=(GLfloat data);
    void operator=(double data);

    void operator=(std::initializer_list<GLint> data);
    void operator=(std::initializer_list<GLuint> data);
    void operator=(std::initializer_list<GLfloat> data);

private:
    GLuint m_VBO;
};
