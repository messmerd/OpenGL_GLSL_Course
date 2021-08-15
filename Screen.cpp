#include "Screen.h"

#include "glad/glad.h"

#include <iostream>

Screen::Screen()
{
    window = nullptr;
    context = nullptr;
}

Screen* Screen::Instance()
{
    // First call will create screen object and all subsequent calls will just return screen pointer
    static Screen* screen = new Screen;
    return screen;
}

bool Screen::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL init failed" << std::endl;
        return false;
    }

    std::cout << "SDL init successful" << std::endl;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 8 bits
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 8 bits
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // 8 bits
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bits
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bit color for each pixel (8+8+8+8)

    // Two frame buffers are used when rending. 
    // One that displays the image, and another that is rendered to behind the scenes:
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Switch on

    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); 

    // 4.4 is the version my graphics card (or graphics card drivers?) supports. Can go lower than this, but not higher.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    window = SDL_CreateWindow("Graphics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        std::cout << "Failed to create context" << std::endl;
        return false;
    }

    if (!gladLoadGL())
    {
        std::cout << "Error loading extensions" << std::endl;
        return false;
    }

    return true;
}

void Screen::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
}

void Screen::Present() const // Swaps buffer
{
    SDL_GL_SwapWindow(window); // Swaps the back and front buffers since we have double buffering on
}

void Screen::Shutdown()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

