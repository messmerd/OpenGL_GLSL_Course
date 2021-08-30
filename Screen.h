#pragma once

#include <SDL.h>

// Singleton
class Screen
{
public:
    static Screen* Instance();

public:
    // Initialize SDL and OpenGL
    bool Initialize();
    void Shutdown();

    void Present() const; // Swaps buffer
    void Clear() const;
    
    
    bool IsInitialized() { return m_IsInitialized; }

private:
    Screen();
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

private:
    bool m_IsInitialized;

    SDL_Window* window;
    SDL_GLContext context;
};



