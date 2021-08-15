#include <windows.h>
#include <GL/gl.h> // Only provides headers for very old OpenGL

#include <iostream>
#include <SDL.h>

#include "Screen.h"
#include "Input.h"

// I'm only using SDL to manage OpenGL context and inputs as a helper for using OpenGL.

bool isAppRunning = true;
Screen* screen = Screen::Instance();
Input* input = Input::Instance();

int main(int argc, char* args[])
{
    screen->Initialize();

    float xPos = 0.0f; // Middle of screen
    float yPos = 0.0f; // Middle of screen

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
        // Render a quad the OLD way
        glBegin(GL_QUADS);

            // Top left color and vertex of quad
            glColor3f(1, 0, 0);
            glVertex3f(xPos - 0.5f, yPos + 0.5f, 0.0f);

            // Top right color and vertex of quad
            glColor3f(0, 1, 0);
            glVertex3f(xPos + 0.5f, yPos + 0.5f, 0.0f);

            // Bottom right color and vertex of quad
            glColor3f(0, 0, 1);
            glVertex3f(xPos + 0.5f, yPos - 0.5f, 0.0f);

            // Bottom left color and vertex of quad
            glColor3f(0, 0, 1);
            glVertex3f(xPos - 0.5f, yPos - 0.5f, 0.0f);

        glEnd();

        screen->Present();
    }

    screen->Shutdown();

    //system("pause");

    return 0;
}
