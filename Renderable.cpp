#include "Renderable.h"

void Renderable::Update()
{
    m_Model = glm::mat4(1.0f);
    m_Model = glm::translate(m_Model, m_Position);
    m_Model = glm::rotate(m_Model, m_RotationAngle, m_RotationAxis);
    m_Model = glm::scale(m_Model, m_Scale);

    m_ModelOut.Set(m_Model);
}

// Position getters/setters

glm::vec3 Renderable::GetPosition()
{
    return m_Position;
}

float Renderable::GetPositionX() { return m_Position.x; }
float Renderable::GetPositionY() { return m_Position.y; }
float Renderable::GetPositionZ() { return m_Position.z; }

void Renderable::SetPosition(float x, float y, float z, bool relative)
{
    if (relative)
    {
        m_Position.x += x;
        m_Position.y += y;
        m_Position.z += z;
    }
    else
    {
        m_Position.x = x;
        m_Position.y = y;
        m_Position.z = z;
    }
}

void Renderable::SetPosition(const glm::vec3& xyz, bool relative)
{
    if (relative)
        m_Position += xyz;
    else
        m_Position = xyz;
}

void Renderable::SetPositionX(float val, bool relative)
{
    if (relative)
        m_Position.x += val;
    else
        m_Position.x = val;
}

void Renderable::SetPositionY(float val, bool relative)
{
    if (relative)
        m_Position.y += val;
    else
        m_Position.y = val;
}

void Renderable::SetPositionZ(float val, bool relative)
{
    if (relative)
        m_Position.z += val;
    else
        m_Position.z = val;
}

// Rotation axis getters/setters

glm::vec3 Renderable::GetRotationAxis()
{
    return m_RotationAxis;
}

void Renderable::SetRotationAxis(float x, float y, float z)
{
    m_RotationAxis.x = x;
    m_RotationAxis.y = y;
    m_RotationAxis.z = z;
}

void Renderable::SetRotationAxis(const glm::vec3& vec)
{
    m_RotationAxis = vec;
}

// Rotation angle getters/setters

float Renderable::GetRotationAngle()
{
    return m_RotationAngle;
}

void Renderable::SetRotationAngle(float angleInRadians)
{
    m_RotationAngle = angleInRadians;
}

// Scale getters/setters

glm::vec3 Renderable::GetScale()
{
    return m_Scale;
}

void Renderable::SetScale(float x, float y, float z)
{
    m_Scale.x = x;
    m_Scale.y = y;
    m_Scale.z = z;
}

void Renderable::SetScale(const glm::vec3& xyz)
{
    m_Scale = xyz;
}
