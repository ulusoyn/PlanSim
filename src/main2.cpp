// #include <iostream>
// #include "CelestialBody.h"
// #include "SolarSystem.h"
// #include "rcamera.h"
// #include "Simmode.h"
// #include "CameraHandler.h"
// #include "rlImGui.h"
// #include "raylib.h"
// #include "imgui.h"

// #include "raymath.h"
// #include <functional>

// enum class EditingSubMode {
//     Idle,           // Default: Nothing selected, waiting for click
//     PlacingBody,    // User clicked and is dragging to define radius/size
//     DraggingBody    // User clicked on an existing body and is moving it
// };

// Vector3 RaycastPlaneIntersection(Ray ray, Vector3 planePoint, Vector3 planeNormal) {
//     // 1. Calculate the distance 't' along the ray to the intersection point.
    
//     // a) Dot product of the normal and the difference between plane point and ray origin
//     float numerator = Vector3DotProduct(planeNormal, Vector3Subtract(planePoint, ray.position));

//     // b) Dot product of the normal and the ray direction
//     float denominator = Vector3DotProduct(planeNormal, ray.direction);

//     // Safety check: If the ray is parallel to the plane, return the origin.
//     if (fabsf(denominator) < 0.0001f) return ray.position;

//     // 2. Calculate the distance 't'
//     float t = numerator / denominator;

//     // 3. Calculate the intersection point P = ray.position + t * ray.direction
//     return Vector3Add(ray.position, Vector3Scale(ray.direction, t));
// }

// int not_main()
// {
//     const int screenWidth = 1440;
//     const int screenHeight = 900;

// 	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
//     InitWindow(screenWidth, screenHeight, "Planet Sim - ImGui Integration Example");
// 	SetTargetFPS(144);
// 	rlImGuiSetup(true);

//     std::unique_ptr<SolarSystem> solarSystem = std::make_unique<SolarSystem>();

//     CameraHandler cameraHandler(
//         Vector3{10.0f, 10.0f, 10.0f}, // position
//         Vector3{0.0f, 0.0f, 0.0f},    // target
//         Vector3{0.0f, 1.0f, 0.0f},    // up
//         60.0f,                        // fovy
//         CAMERA_PERSPECTIVE            // projection mode
//     );

    
//     bool isCursorVisible = false;
//     bool run = true;

//     bool showDemoWindow = true;

// #ifdef IMGUI_HAS_DOCK
// 	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
// #endif

//     DisableCursor();   // Limit cursor to relative movement inside the window

//     solarSystem->AddBody("Sun", 10.0f, 5.0f, YELLOW, Vector3{0,0,0}, Vector3{0,0,0});

//     Simmode CurrentMode = Simmode::CameraControl;
//     EditingSubMode CurrentEditSubMode = EditingSubMode::Idle;
    
//     Vector3 dragStartPos;
//     float ghostRadius = 0.0f;
//     bool isDragging = false;

//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         solarSystem->Update(GetFrameTime());
//         solarSystem->ApplyGravity();



//         if(IsKeyPressed((KEY_F)))
//         {
//             if (CurrentMode == Simmode::EditingMode)
//             {
//                 CurrentMode = Simmode::CameraControl;
//                 DisableCursor();
//             }
//             else if (CurrentMode == Simmode::CameraControl)
//             {
//                 CurrentMode = Simmode::EditingMode;
//                 EnableCursor();
//             }
//         }

//         if (IsKeyPressed(KEY_Z)) cameraHandler.SelectTarget(Vector3{0.0f, 0.0f, 0.0f});


//         // Switch camera projection
//         if (CurrentMode == Simmode::CameraControl && IsKeyPressed(KEY_P))
//         {
//             cameraHandler.SwitchProjection();
//         }

//         if(CurrentMode == Simmode::EditingMode)
//         {
//             if (IsKeyPressed(KEY_C))
//             {
//                 if (CurrentEditSubMode == EditingSubMode::Idle)
//                 {
//                     CurrentEditSubMode = EditingSubMode::PlacingBody;
//                 }
//                 else if (CurrentEditSubMode == EditingSubMode::PlacingBody)
//                 {
//                     CurrentEditSubMode = EditingSubMode::Idle;
//                 }
//                 CurrentEditSubMode = EditingSubMode::PlacingBody;
//                 std::cout << "Placing Body" << std::endl;
//             }

//             if (IsKeyPressed(KEY_T))
//             {
//                 if (CurrentEditSubMode == EditingSubMode::Idle)
//                 {
//                     CurrentEditSubMode = EditingSubMode::DraggingBody;
//                 }
//                 else if (CurrentEditSubMode == EditingSubMode::DraggingBody)
//                 {
//                     CurrentEditSubMode = EditingSubMode::Idle;
//                 }
//                 CurrentEditSubMode = EditingSubMode::PlacingBody;
//                 std::cout << "Dragging Body" << std::endl;
//             }
        
//             if(CurrentEditSubMode == EditingSubMode::PlacingBody){
//                 if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//                 {
//                     isDragging = true;
//                     Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
//                     Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };

//                     Ray startRay = GetMouseRay(GetMousePosition(), cameraHandler.GetCamera());

//                     // Store the first intersection point
//                     dragStartPos = RaycastPlaneIntersection(startRay, planePoint, planeNormal);
//                 }
//                 if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//                 {
//                     solarSystem->AddBody("NewPlanet", ghostRadius * SimPhysics::UNIT_MASS, ghostRadius, ORANGE, dragStartPos, Vector3{0.0f, 0.0f, 0.0f});
//                     isDragging = false;
//                 }

//                 if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
//                 {
//                     Vector3 planePoint = { 0.0f, 0.0f, 0.0f };
//                     Vector3 planeNormal = { 0.0f, 0.0f, 1.0f };

//                     // --- 2. Calculate the Ray for the current mouse position ---
//                     Ray currentRay = GetMouseRay(GetMousePosition(), cameraHandler.GetCamera());

//                     // --- 3. Determine the Ghost Point (The current 3D point on the plane) ---
//                     Vector3 current3DPosition = RaycastPlaneIntersection(currentRay, planePoint, planeNormal);

//                     // --- 4. Calculate the Radius ---
//                     // The distance between the initial click point and the current point on the plane
//                     ghostRadius = Vector3Distance(dragStartPos, current3DPosition);

//                     std::cout << "Ghost Radius: " << ghostRadius << std::endl;

//                     // Optional: Set a minimum radius to prevent division by zero later
//                     if (ghostRadius < 0.1f) ghostRadius = 0.1f;
//                 }
//             }
//         }
        
        

//         if(CurrentMode == Simmode::CameraControl) cameraHandler.CameraUpdate();


//         // Drawing begins
//         //----------------------------------------------------------------------------------
//         BeginDrawing();
//             ClearBackground(DARKGRAY);


//             BeginMode3D(cameraHandler.GetCamera());

//                 if (isDragging)
//                 {         
//                     DrawSphereWires(dragStartPos, ghostRadius + 0.1f, 16, 16, Fade(BLACK, 0.3f));
//                 }

//                 DrawGrid(20, 1.0f);
//                 solarSystem->Draw();

//             EndMode3D();

//             // Drawing everything before rlImGui begins. 

//             rlImGuiBegin();

// // Add docking to the ImGui viewport
// #ifdef IMGUI_HAS_DOCK
// 		ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
// #endif

//         // start ImGui Conent

//             // show ImGui Content
//             bool open = true;
//             ImGui::ShowDemoWindow(&open);

//             open = true;

//                     // show a simple menu bar
//             if (ImGui::BeginMainMenuBar())
//             {
//                 if (ImGui::BeginMenu("File"))
//                 {
//                     if (ImGui::MenuItem("Quit"))
//                         run = false;

//                     ImGui::EndMenu();
//                 }

//                 if (ImGui::BeginMenu("Window"))
//                 {
//                     if (ImGui::MenuItem("Demo Window", nullptr, showDemoWindow))
//                         showDemoWindow = !showDemoWindow;

//                     ImGui::EndMenu();
//                 }
//                 ImGui::EndMainMenuBar();
//             }

//             // show some windows
        
//             if (showDemoWindow)
//                 ImGui::ShowDemoWindow(&showDemoWindow);

//             if (ImGui::Begin("Test Window"))
//             {
//                 ImGui::TextUnformatted("Another window");
//                 DrawSphere(Vector3{0,0,0}, 1.0f, RED);
//             }
//             ImGui::End();
//             rlImGuiEnd();
//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }
//     rlImGuiShutdown();

//     CloseWindow();

//     return 0;
// }