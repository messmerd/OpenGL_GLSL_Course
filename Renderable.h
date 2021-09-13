#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Buffer.h"
#include "Shader.h"

class Renderable : public Buffer
{
public:
    Renderable()
        : Buffer(), m_ModelOut()
    {
        // Set model matrix to identity matrix
        m_Model = glm::mat4(1.0f);

        m_Position = glm::vec3(0.0f);
        m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_RotationAngle = 0.0f;
        m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    
    Renderable(const char* modelName, const char* vertexName, const char* colorName)
        : Buffer(vertexName, colorName), m_ModelOut(modelName)
    {
        // Set model matrix to identity matrix
        m_Model = glm::mat4(1.0f);

        m_Position = glm::vec3(0.0f);
        m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_RotationAngle = 0.0f;
        m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    virtual ~Renderable()
    {
        Destroy();
    };

    void Update();
    virtual void Render() const = 0;

    virtual void Set(GLfloat* vertexData, GLsizeiptr vertexSize, GLfloat* colorData, GLsizeiptr colorSize) = 0;

    // Position getters/setters

    glm::vec3 GetPosition();
    float GetPositionX();
    float GetPositionY();
    float GetPositionZ();

    void SetPosition(float x, float y, float z, bool relative = false);
    void SetPosition(const glm::vec3& xyz, bool relative = false);
    void SetPositionX(float val, bool relative = false);
    void SetPositionY(float val, bool relative = false);
    void SetPositionZ(float val, bool relative = false);

    // Rotation axis getters/setters

    glm::vec3 GetRotationAxis();
    void SetRotationAxis(float x, float y, float z);
    void SetRotationAxis(const glm::vec3& vec);

    // Rotation angle getters/setters

    float GetRotationAngle();
    void SetRotationAngle(float angleInRadians);
    
    // Scale getters/setters

    glm::vec3 GetScale();
    void SetScale(float x, float y, float z);
    void SetScale(const glm::vec3& xyz);

protected:
    glm::mat4 m_Model;

    glm::vec3 m_Position;
    glm::vec3 m_RotationAxis;
    float m_RotationAngle; // In radians
    glm::vec3 m_Scale;

private:
    Uniform m_ModelOut;
};
