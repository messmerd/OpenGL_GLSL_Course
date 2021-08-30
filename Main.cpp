#include <SDL.h>
#include "glad/glad.h"

#include "Screen.h"
#include "Input.h"
#include "Shader.h"
#include "Quad.h"

#include <vector>
#include <iostream>

// I'm only using SDL to manage OpenGL context and inputs as a helper for using OpenGL.

bool isAppRunning = true;
Screen* screen = Screen::Instance();
Input* input = Input::Instance();
Shader* shaders = Shader::Instance();

std::vector<Renderable*> objectsToRender;

int main(int argc, char* args[])
{
    // Initialize SDL and OpenGL
    if (!screen->Initialize())
        return 1;

    // Create shader program, create/compile/attach shaders, and link shaders to program
    if (!shaders->Initialize("Shaders/Main.vert", "Shaders/Main.frag"))
        return 1;
    
    // Create and set quad
    Quad quad("vertexIn", "colorIn");
    quad.Set(); // Using default quad - can change later
    
    // List of objects to render
    objectsToRender.push_back(&quad);

    // Quad coordinates (middle of screen)
    float xPos = 0.0f;
    float yPos = 0.0f;

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
        for (const Renderable* object : objectsToRender)
        {
            object->Render();
        }

        screen->Present();
    }

    // Detach shaders and destroy shader program
    shaders->Destroy();
    
    // Shutdown SDL
    screen->Shutdown();

    //system("pause");

    return 0;
}
