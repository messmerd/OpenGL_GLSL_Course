#include "Input.h"

#include <iostream>

Input::Input()
{
    m_IsCloseClicked = false;
    m_IsKeyPressed = false;

    m_KeyUp = '\0';
    m_KeyDown = '\0';

    m_IsLeftButtonClicked = false;
    m_IsRightButtonClicked = false;
    m_IsMiddleButtonClicked = false;

    m_MousePositionX = 0;
    m_MousePositionY = 0;

    m_MouseMotionX = 0;
    m_MouseMotionY = 0;
}

Input* Input::Instance()
{
    // First call will create input object and all subsequent calls will just return input pointer
    static Input* input = new Input;
    return input;
}

void Input::Update()
{
    SDL_Event events;

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_QUIT:
            m_IsCloseClicked = true;
            break;
        case SDL_KEYDOWN:
            m_IsKeyPressed = true;
            m_KeyDown = events.key.keysym.sym;
            break;
        case SDL_KEYUP:
            m_IsKeyPressed = false;
            m_KeyUp = events.key.keysym.sym;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            switch (events.button.button)
            {
            case SDL_BUTTON_LEFT:
                m_IsLeftButtonClicked = events.type == SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_BUTTON_RIGHT:
                m_IsRightButtonClicked = events.type == SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_BUTTON_MIDDLE:
                m_IsMiddleButtonClicked = events.type == SDL_MOUSEBUTTONDOWN;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            m_MouseMotionX = events.motion.xrel;
            m_MouseMotionY = events.motion.yrel;
            m_MousePositionX = events.motion.x;
            m_MousePositionY = events.motion.y;
            break;


        }
    }
}

