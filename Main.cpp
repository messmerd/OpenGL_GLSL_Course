#include <iostream>
#include <SDL.h>

#include "glad/glad.h"

#include "Screen.h"
#include "Input.h"
#include "Shader.h"

// I'm only using SDL to manage OpenGL context and inputs as a helper for using OpenGL.

bool isAppRunning = true;
Screen* screen = Screen::Instance();
Input* input = Input::Instance();
Shader* shaders = Shader::Instance();

int main(int argc, char* args[])
{
    screen->Initialize();

    // Create shader program and shader objects
    if (!shaders->CreateProgram() || !shaders->CreateShaders())
        return 1;

    // Compile vertex shader
    if (!shaders->CompileShaders("Shaders/Main.vert", Shader::ShaderType::VERTEX_SHADER))
        return 1;

    // Compile fragment shader
    if (!shaders->CompileShaders("Shaders/Main.frag", Shader::ShaderType::FRAGMENT_SHADER))
        return 1;

    // Attach shaders to shader program
    shaders->AttachShaders();

    // Link shaders to shader program
    if (!shaders->LinkProgram())
        return 1;

    float xPos = 0.0f; // Middle of screen
    float yPos = 0.0f; // Middle of screen

    // Data that represents vertices for quad
    GLfloat vertices[] = {  -1.0f,  +1.0f,  0.0f,
                            +1.0f,  +1.0f,  0.0f,
                            -1.0f,  -1.0f,  0.0f, // Triangle 1

                            -1.0f,  -1.0f,  0.0f,
                            +1.0f,  +1.0f,  0.0f,
                            +1.0f,  -1.0f,  0.0f }; // Triangle 2

    // Data that represents colors for quad
    GLfloat colors[] = {    0.0f,   0.0f,   1.0f,
                            0.0f,   0.0f,   1.0f,
                            1.0f,   1.0f,   1.0f, // Triangle 1

                            1.0f,   1.0f,   1.0f,
                            0.0f,   0.0f,   1.0f,
                            1.0f,   1.0f,   1.0f }; // Triangle 2

    //Uniform time = shaders->GetUniform("time");
    //time = 5;

    VertexAttribute vertexAttrib = shaders->GetVectorAttribute("vertexIn");
    VertexAttribute colorAttrib = shaders->GetVectorAttribute("colorIn");

    GLuint vao = shaders->BeginVAOBind();
        vertexAttrib.Bind(vertices, sizeof(vertices));
        colorAttrib.Bind(colors, sizeof(colors));
    shaders->EndVAOBind();

    //====================================================================

    while (isAppRunning)
    {
        screen->Clear();

        input->Update();

        isAppRunning = !input->IsCloseClicked();

        if (input->IsKeyPressed())
        {
            if (input->GetKeyDown() == 'w')
            {
                yPos += 0.01f;
            }
            else if (input->GetKeyDown() == 'a')
            {
                xPos -= 0.01f;
            }
            else if (input->GetKeyDown() == 's')
            {
                yPos -= 0.01f;
            }
            else if (input->GetKeyDown() == 'd')
            {
                xPos += 0.01f;
            }
        }
        
        // Update/render stuff
        glBindVertexArray(vao); // Bind
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0); // Unbind

        screen->Present();
    }

    vertexAttrib.Destroy();
    colorAttrib.Destroy();
    glDeleteVertexArrays(1, &vao);

    shaders->DetachShaders();
    shaders->DetachShaders();
    shaders->DestroyProgram();
    screen->Shutdown();

    //system("pause");

    return 0;
}
