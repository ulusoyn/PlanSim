#pragma once

#include "raylib.h"

enum class ButtonState{
    JustPressed, Held, JustReleased, Released
};

class InputHandler {
private:
    // The button state can only one of the states in enum ButtonState
    ButtonState m_buttonState;
    const float DOUBLE_CLICK_TIME = 0.3f;   // time needed to consider a double click

    int m_keyCode = -1;                     // The key or mouse button code being tracked

    bool m_wasDownLastState;                // True if the button was double clicked
    bool m_doubleClicked;

    float m_lastHoldDuration;
    float m_holdTime;                       // Time past while button is held down
    float m_timeSpan;                       // Time past since last button state change
    float m_lastClicked;                    // Time past since last click

public:
    InputHandler(int keyCode);
    
    bool IsJustPressed() const { return m_buttonState == ButtonState::JustPressed; }

    bool IsHeld() const { return m_buttonState == ButtonState::Held; }

    bool IsJustReleased() const { return m_buttonState == ButtonState::JustReleased; }

    bool IsReleased() const { return m_buttonState == ButtonState::Released; }

    void Update();
};