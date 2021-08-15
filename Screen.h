#pragma once

#include <SDL.h>

// Singleton
class Screen
{
public:
    static Screen* Instance();

public:
    bool Initialize();
    void Clear() const;
    void Present() const; // Swaps buffer
    void Shutdown() const;

private:
    Screen();
    Screen(const Screen&);
    Screen& operator=(const Screen&);

private:
    SDL_Window* window;
    SDL_GLContext context;
};



