#pragma once

#include "raylib.h"

enum class ButtonState{
    justPressed, Held, justReleased, released
};


class InputHandler {
private:
    // The button state can only one of the states in enum ButtonState
    ButtonState m_buttonState;

    int m_buttonCode = -1; // The key or mouse button code being tracked

    bool m_doubleClicked;


    float m_timeSpan;
    float m_lastClicked;

public:
    InputHandler(int buttonCode);
    
    bool isJustPressed() const {
        return m_buttonState == ButtonState::justPressed;
    }

    bool isHeld() const {
        return m_buttonState == ButtonState::Held;
    }

    bool isJustReleased() const {
        return m_buttonState == ButtonState::justReleased;
    }

    bool isReleased() const {
        return m_buttonState == ButtonState::released;
    }

    void Update();




};