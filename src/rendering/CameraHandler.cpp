#include "CameraHandler.h"
#include "rcamera.h"
#include <iostream>

CameraHandler::CameraHandler( Vector3 position, Vector3 target, Vector3 up, float fovy, int projection_mode)
    : m_projectionMode(projection_mode)
{
    m_camera = {0};
    m_camera.position = position;
    m_camera.target = target;
    m_camera.up = up;
    m_camera.fovy = fovy;
    m_camera.projection = CAMERA_PERSPECTIVE; // Default to perspective
}

void CameraHandler::ChangeProjection(int projection_mode)
{
    try
    {
        m_projectionMode = projection_mode;
    }
    catch(...)
    {
        std::cerr << "Error: Invalid projection mode. Keeping previous mode." << std::endl;
        return;
    }
    switch (projection_mode)
    {
        case CAMERA_PERSPECTIVE:
            m_camera.projection = CAMERA_PERSPECTIVE;
            break;
        case CAMERA_ORTHOGRAPHIC:
            m_camera.projection = CAMERA_ORTHOGRAPHIC;
            break;
    }
}

void CameraHandler::CameraUpdate()
{
    switch (m_cameraMode)
    {
        case CAMERA_FIRST_PERSON:
            UpdateCamera(&m_camera, CAMERA_FIRST_PERSON);
            break;
        case CAMERA_THIRD_PERSON:
            UpdateCamera(&m_camera, CAMERA_THIRD_PERSON);
            break;
        case CAMERA_FREE:
            UpdateCamera(&m_camera, CAMERA_FREE);
            break;
        case CAMERA_ORBITAL:
            UpdateCamera(&m_camera, CAMERA_ORBITAL);
            break;
        default:
            std::cerr << "Error: Invalid camera mode. No update performed." << std::endl;
            break;
    }
}

void CameraHandler::SwitchProjection()
{
    if (m_camera.projection == CAMERA_PERSPECTIVE)
    {
        // Create isometric view
        m_cameraMode = CAMERA_THIRD_PERSON;
        // Note: The target distance is related to the render distance in the orthographic projection
        m_camera.position = Vector3{ 0.0f, 2.0f, -100.0f };
        m_camera.target = Vector3{ 0.0f, 2.0f, 0.0f };
        m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        m_camera.projection = CAMERA_ORTHOGRAPHIC;
        m_camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
        CameraYaw(&m_camera, -135*DEG2RAD, true);
        CameraPitch(&m_camera, -45*DEG2RAD, true, true, false);
        ChangeProjection(CAMERA_ORTHOGRAPHIC);
    }
    else if (m_camera.projection == CAMERA_ORTHOGRAPHIC)
    {
        m_cameraMode = CAMERA_THIRD_PERSON;
        m_camera.position = Vector3{ 0.0f, 2.0f, 10.0f };
        m_camera.target = Vector3{ 0.0f, 2.0f, 0.0f };
        m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        m_camera.projection = CAMERA_PERSPECTIVE;
        m_camera.fovy = 60.0f;
    }
}


