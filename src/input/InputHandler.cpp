#include "input/InputHandler.h"


InputHandler::InputHandler(int keyCode)
    : m_keyCode(keyCode), m_timeSpan(0.0f), m_lastClicked(0.0f), m_buttonState(ButtonState::Released)
{
    m_doubleClicked = false;
    m_lastHoldDuration = 0.0f;
    m_holdTime = 0.0f;
    m_wasDownLastState = false;
}

void InputHandler::Update()
{
    bool isKeyDown = IsKeyDown(m_keyCode);
    m_doubleClicked = false;

    // if it was not down (up) last state and is down now, then it is JustPressed 
    if (!m_wasDownLastState && isKeyDown)
    {
        m_buttonState = ButtonState::JustPressed;
        m_holdTime = 0.0f;

        // if 0.3s is not passed since last click, it is a double click
        if (m_lastClicked < DOUBLE_CLICK_TIME) 
        {
            m_doubleClicked = true;
        }
        else
        {
            m_doubleClicked = false;
        }

        m_lastClicked = 0.0f;
    }
    
    // if it was down last frame and still down, it is held
    else if (m_wasDownLastState && isKeyDown)
    {
        m_buttonState = ButtonState::Held;
        m_holdTime += GetFrameTime();
    }
    // if it was down last state and right now it is up, then it is JustReleased
    else if (m_wasDownLastState && !isKeyDown)
    {
        m_buttonState = ButtonState::JustReleased;
        m_lastHoldDuration = m_holdTime;
    }
    // if it was not down and still up, it is Released
    else
    {
        m_buttonState = ButtonState::Released;
    }

    m_wasDownLastState = isKeyDown;
    m_lastClicked += GetFrameTime();
}