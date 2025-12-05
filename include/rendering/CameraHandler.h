#pragma once
#include "raylib.h"
#include "rcamera.h"

class CameraHandler {
protected:
    Camera3D m_camera;
    int m_projectionMode;
    int m_cameraMode = CAMERA_FIRST_PERSON;

public: 
    CameraHandler(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection_mode);
    void CameraUpdate();
    void ChangeCameraMode(int camera_mode) { m_cameraMode = camera_mode; }
    void ChangeProjection(int camera_mode);
    void SwitchProjection();
    void SelectTarget(Vector3 target) { m_camera.target = target; }
    Camera3D GetCamera() { return m_camera; }
    int GetProjectionMode() { return m_projectionMode; }
};