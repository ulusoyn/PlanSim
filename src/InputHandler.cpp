#include "InputHandler.h"


InputHandler::InputHandler(int buttonCode)
    : m_buttonCode(buttonCode), m_timeSpan(0.0f), m_doubleClicked(false), m_lastClicked(0.0f), m_buttonState(ButtonState::released)
{

}

void InputHandler::Update()
{
    if (IsKeyPressed(m_buttonCode))
    {
        if (m_lastClicked < 0.3)
        {
            m_doubleClicked = true;
        }
        else
        {
            m_doubleClicked = false;
            m_lastClicked = 0.0f;
        }
        m_buttonState = ButtonState::justPressed;
        m_timeSpan = 0.0f;
    }

    if (IsKeyReleased(m_buttonCode))
    {
        m_buttonState = ButtonState::justReleased;
        m_timeSpan = 0.0f;
    }


    m_timeSpan += GetFrameTime();
    m_lastClicked += GetFrameTime();
    if (m_timeSpan >= 0.1f)
    {
        if(m_buttonState == ButtonState::justPressed)
        {
            m_buttonState = ButtonState::Held;
        }
        if (m_buttonState == ButtonState::justReleased)
        {
            m_buttonState = ButtonState::released;
        }
        m_timeSpan = 0.0f;
    }
}