#pragma once

#include <string>
#include "glad/glad.h"

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

private:
    Shader();
    Shader(const Shader&);
    Shader& operator=(Shader&);

private:
    GLuint m_ShaderProgramId;
    GLuint m_VertexShaderId;
    GLuint m_FragmentShaderId;
};
