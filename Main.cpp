#include <iostream>
#include <SDL.h>
#include "Screen.h"

#include <windows.h>
#include <GL/gl.h> // Only provides headers for very old OpenGL

// I'm only using SDL to manage OpenGL context and inputs as a helper for using OpenGL.

bool isAppRunning = true;
Screen* screen = Screen::Instance();

int main(int argc, char* args[])
{
    screen->Initialize();

    while (isAppRunning)
    {
        screen->Clear();

        // Update/render stuff
        
        // Render a quad the OLD way
        glBegin(GL_QUADS);

            // Top left color and vertex of quad
            glColor3f(1, 0, 0);
            glVertex3f(-0.5f, 0.5f, 0.0f);

            // Top right color and vertex of quad
            glColor3f(0, 1, 0);
            glVertex3f(0.5f, 0.5f, 0.0f);

            // Bottom right color and vertex of quad
            glColor3f(0, 0, 1);
            glVertex3f(0.5f, -0.5f, 0.0f);

            // Bottom left color and vertex of quad
            glColor3f(0, 0, 1);
            glVertex3f(-0.5f, -0.5f, 0.0f);

        glEnd();

        screen->Present();
    }

    screen->Shutdown();

    //system("pause");

    return 0;
}
