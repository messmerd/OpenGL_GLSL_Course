#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "Input.h"

extern Input* input;

Camera::Camera()
    : m_ViewOut("view"), m_ProjectionOut("proj")
{
    m_View = glm::mat4(1.0f);
    m_Projection = glm::mat4(1.0f);

    m_Position = glm::vec3(0.0f);
    m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
    m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::Set3DView()
{
    GLfloat FOV = 45.0f; // Field of view
    GLfloat aspectRatio = 1280.0f / 720.0f; // TODO: In the future this shouldn't be hard-coded

    // Set projection matrix using field of view, aspect ratio, near clip, and far clip
    m_Projection = glm::perspective(FOV, aspectRatio, 0.001f, 1000.0f);
    m_ProjectionOut.Set(m_Projection);
}

void Camera::Update()
{
    if (input->IsKeyPressed())
    {
        if (input->GetKeyDown() == 'w')
        {
            m_Position.z += -0.001f;
        }
        else if (input->GetKeyDown() == 'a')
        {
            m_Position.x += -0.001f;
        }
        else if (input->GetKeyDown() == 's')
        {
            m_Position.z += 0.001f;
        }
        else if (input->GetKeyDown() == 'd')
        {
            m_Position.x += 0.001f;
        }
        else if (input->GetKeyDown() == 'q')
        {
            m_Position.y += 0.001f;
        }
        else if (input->GetKeyDown() == 'e')
        {
            m_Position.y += -0.001f;
        }
    }

    m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
    m_ViewOut.Set(m_View);
}
