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

// This is a temporary function until I have a GameObject class
void HandleKeyPress(Quad& obj);

int main(int argc, char* args[])
{
    // Initialize SDL and OpenGL
    if (!screen->Initialize())
        return 1;

    // Create shader program, create/compile/attach shaders, and link shaders to program
    if (!shaders->Initialize("Shaders/Main.vert", "Shaders/Main.frag"))
        return 1;
    
    // Create and set quad
    Quad quad("model", "vertexIn", "colorIn");
    quad.Set(); // Using default quad - can change later
    
    // List of objects to render
    objectsToRender.push_back(&quad);

    //====================================================================

    while (isAppRunning)
    {
        screen->Clear();

        input->Update();

        isAppRunning = !input->IsCloseClicked();

        HandleKeyPress(quad);
        
        // Update/render stuff
        for (Renderable* object : objectsToRender)
        {
            object->Update();
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

void HandleKeyPress(Quad& obj)
{
    if (input->IsKeyPressed())
    {
        if (input->GetKeyDown() == 'w')
        {
            obj.SetPositionY(0.001f, true);
        }
        else if (input->GetKeyDown() == 'a')
        {
            obj.SetPositionX(-0.001f, true);
        }
        else if (input->GetKeyDown() == 's')
        {
            obj.SetPositionY(-0.001f, true);
        }
        else if (input->GetKeyDown() == 'd')
        {
            obj.SetPositionX(0.001f, true);
        }
    }
}
