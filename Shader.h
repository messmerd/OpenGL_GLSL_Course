#pragma once

#include <string>
#include "glad/glad.h"

class Uniform; // Forward definition

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

    Uniform GetUniform(const char* name);

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

class Uniform
{
friend class Shader;

private:
    Uniform();
    Uniform(GLuint shaderProgramId, const char* name);
    //Uniform(const Uniform& u); // Prevent copy constructor from being used

public:
    bool Load(GLuint shaderProgramId, const char* name);
    bool IsValid() const { return m_Id != -1; }

    void operator=(GLint data);
    void operator=(GLuint data);
    void operator=(GLfloat data);
    void operator=(double data);

    void operator=(std::initializer_list<GLint> data);
    void operator=(std::initializer_list<GLuint> data);
    void operator=(std::initializer_list<GLfloat> data);
    
private:
    GLint m_Id;
};
