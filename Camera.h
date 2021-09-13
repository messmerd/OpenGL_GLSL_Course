#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "Shader.h"

class Camera
{
public:
    Camera();

    void Update();

protected:
    glm::mat4 m_View;
    Uniform m_ViewOut;

    glm::vec3 m_Position;
    glm::vec3 m_Direction;
    glm::vec3 m_Up;
};
