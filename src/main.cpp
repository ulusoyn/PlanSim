#include <iostream>
#include "CelestialBody.h"
#include "SolarSystem.h"
#include "rcamera.h"
#include "Simmode.h"
#include "raymath.h"
#include <functional>

enum class EditingSubMode {
    Idle,           // Default: Nothing selected, waiting for click
    PlacingBody,    // User clicked and is dragging to define radius/size
    DraggingBody    // User clicked on an existing body and is moving it
};

Vector3 RaycastPlaneIntersection(Ray ray, Vector3 planePoint, Vector3 planeNormal) {
    // 1. Calculate the distance 't' along the ray to the intersection point.
    
    // a) Dot product of the normal and the difference between plane point and ray origin
    float numerator = Vector3DotProduct(planeNormal, Vector3Subtract(planePoint, ray.position));

    // b) Dot product of the normal and the ray direction
    float denominator = Vector3DotProduct(planeNormal, ray.direction);

    // Safety check: If the ray is parallel to the plane, return the origin.
    if (fabsf(denominator) < 0.0001f) return ray.position;

    // 2. Calculate the distance 't'
    float t = numerator / denominator;

    // 3. Calculate the intersection point P = ray.position + t * ray.direction
    return Vector3Add(ray.position, Vector3Scale(ray.direction, t));
}

int main()
{
    const int screenWidth = 1440;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Planet Sim");

    std::unique_ptr<SolarSystem> solarSystem = std::make_unique<SolarSystem>();

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = Vector3{10.0f, 10.0f, 10.0f}; // Camera position
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;
    
    bool isCursorVisible = false;
    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    solarSystem->AddBody("Sun", 1000.0f, 5.0f, YELLOW, Vector3{0,0,0}, Vector3{0,0,0});

    Simmode CurrentMode = Simmode::CameraControl;
    EditingSubMode CurrentEditSubMode = EditingSubMode::Idle;
    
    Vector3 dragStartPos;
    float ghostRadius = 0.0f;
    bool isDragging = false;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        solarSystem->Update(GetFrameTime());
        solarSystem->ApplyGravity();
        // Key input to toggle cursor visibility
        
        if(IsKeyPressed((KEY_F)))
        {
            if (CurrentMode == Simmode::EditingMode)
            {
                CurrentMode = Simmode::CameraControl;
                DisableCursor();
            }
            else if (CurrentMode == Simmode::CameraControl)
            {
                CurrentMode = Simmode::EditingMode;
                EnableCursor();
            }
        }

        if (IsKeyPressed(KEY_Z)) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };


        // Switch camera projection
        if (CurrentMode == Simmode::CameraControl && IsKeyPressed(KEY_P))
        {
            if (camera.projection == CAMERA_PERSPECTIVE)
            {
                // Create isometric view
                cameraMode = CAMERA_THIRD_PERSON;
                // Note: The target distance is related to the render distance in the orthographic projection
                camera.position = Vector3{ 0.0f, 2.0f, -100.0f };
                camera.target = Vector3{ 0.0f, 2.0f, 0.0f };
                camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
                camera.projection = CAMERA_ORTHOGRAPHIC;
                camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
                CameraYaw(&camera, -135*DEG2RAD, true);
                CameraPitch(&camera, -45*DEG2RAD, true, true, false);
            }
            else if (camera.projection == CAMERA_ORTHOGRAPHIC)
            {
                // Reset to default view
                cameraMode = CAMERA_THIRD_PERSON;
                camera.position = Vector3{ 0.0f, 2.0f, 10.0f };
                camera.target = Vector3{ 0.0f, 2.0f, 0.0f };
                camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
                camera.projection = CAMERA_PERSPECTIVE;
                camera.fovy = 60.0f;
            }
        }

        if(CurrentMode == Simmode::EditingMode)
        {
            if (IsKeyPressed(KEY_C))
            {
                if (CurrentEditSubMode == EditingSubMode::Idle)
                {
                    CurrentEditSubMode = EditingSubMode::PlacingBody;
                }
                else if (CurrentEditSubMode == EditingSubMode::PlacingBody)
                {
                    CurrentEditSubMode = EditingSubMode::Idle;
                }
                CurrentEditSubMode = EditingSubMode::PlacingBody;
                std::cout << "Placing Body" << std::endl;
            }

            if (IsKeyPressed(KEY_T))
            {
                if (CurrentEditSubMode == EditingSubMode::Idle)
                {
                    CurrentEditSubMode = EditingSubMode::DraggingBody;
                }
                else if (CurrentEditSubMode == EditingSubMode::DraggingBody)
                {
                    CurrentEditSubMode = EditingSubMode::Idle;
                }
                CurrentEditSubMode = EditingSubMode::PlacingBody;
                std::cout << "Dragging Body" << std::endl;
            }
        
            if(CurrentEditSubMode == EditingSubMode::PlacingBody){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    isDragging = true;
                    Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
                    Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };

                    Ray startRay = GetMouseRay(GetMousePosition(), camera);

                    // Store the first intersection point
                    dragStartPos = RaycastPlaneIntersection(startRay, planePoint, planeNormal);
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    solarSystem->AddBody("NewPlanet", ghostRadius * SimPhysics::UNIT_MASS, ghostRadius, BLUE, dragStartPos, Vector3{0.0f, 0.0f, 0.0f});
                    isDragging = false;
                }

                if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
                    Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };

                    // --- 2. Calculate the Ray for the current mouse position ---
                    Ray currentRay = GetMouseRay(GetMousePosition(), camera);

                    // --- 3. Determine the Ghost Point (The current 3D point on the plane) ---
                    Vector3 current3DPosition = RaycastPlaneIntersection(currentRay, planePoint, planeNormal);

                    // --- 4. Calculate the Radius ---
                    // The distance between the initial click point and the current point on the plane
                    ghostRadius = Vector3Distance(dragStartPos, current3DPosition);

                    std::cout << "Ghost Radius: " << ghostRadius << std::endl;

                    // Optional: Set a minimum radius to prevent division by zero later
                    if (ghostRadius < 0.1f) ghostRadius = 0.1f;
                }
            }
        }
        
        

        if(CurrentMode == Simmode::CameraControl) UpdateCamera(&camera, cameraMode);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                if (isDragging)
                {         
                    DrawSphereWires(dragStartPos, ghostRadius + 0.1f, 16, 16, Fade(BLACK, 0.3f));
                }

                DrawGrid(20, 1.0f);
                solarSystem->Draw();

            EndMode3D();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}