#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.h"

class Camera
{
public:
    Camera();

    void Set3DView();
    void Update();

protected:
    glm::mat4 m_View;
    Uniform m_ViewOut;

    glm::mat4 m_Projection;
    Uniform m_ProjectionOut;

    glm::vec3 m_Position;
    glm::vec3 m_Direction;
    glm::vec3 m_Up;
};
