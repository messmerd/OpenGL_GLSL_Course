#pragma once

#include <SDL.h>

class Input
{
public:
    static Input* Instance();

public:
    bool IsCloseClicked() { return m_IsCloseClicked; }
    bool IsKeyPressed() { return m_IsKeyPressed; }

    char GetKeyUp() { return m_KeyUp; }
    char GetKeyDown() { return m_KeyDown; }

    bool IsLeftButtonClicked() { return m_IsLeftButtonClicked; }
    bool IsRightButtonClicked() { return m_IsRightButtonClicked; }
    bool IsMiddleButtonClicked() { return m_IsMiddleButtonClicked; }

    int GetMousePositionX() { return m_MousePositionX; }
    int GetMousePositionY() { return m_MousePositionY; }

    int GetMouseMotionX() { return m_MouseMotionX; }
    int GetMouseMotionY() { return m_MouseMotionY; }

public:
    void Update();

private:
    Input();
    Input(const Input&);
    Input& operator=(Input&);

private:

    // Key release events
    char m_KeyUp;
    char m_KeyDown;

    bool m_IsCloseClicked;
    bool m_IsKeyPressed;

    bool m_IsLeftButtonClicked;
    bool m_IsRightButtonClicked;
    bool m_IsMiddleButtonClicked;

    int m_MousePositionX;
    int m_MousePositionY;

    int m_MouseMotionX;
    int m_MouseMotionY;
};

