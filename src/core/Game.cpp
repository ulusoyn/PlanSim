#include "pch.h"
#include "core/Game.h"



Game::Game(const int screenWidth, const int screenHeight)
    : m_cameraHandler(
          Vector3{10.0f, 10.0f, 10.0f}, // position
          Vector3{0.0f, 0.0f, 0.0f},    // target
          Vector3{0.0f, 1.0f, 0.0f},    // up
          60.0f,                        // fovy
          CAMERA_PERSPECTIVE            // projection mode
      ),
      screenWidth(screenWidth),
      screenHeight(screenHeight),
      m_solarSystem(SolarSystem()),
      m_inputContext(InputContext()),
      m_outputContext(OutputContext()),
      m_currentTool(Tools::None),
      m_isCursorVisible(true),
      m_isRunning(true),
      m_keyBindings(KeyBindings()),
      m_services(GameServices{this, m_cameraHandler.GetCamera(), &m_solarSystem}),
      m_inputManager(InputManager(m_services, m_inputContext, m_outputContext, m_keyBindings)),
      m_showDemoWindow(true),
      m_guiService(GUIService(m_outputContext, m_services))
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Solar System");
    rlImGuiSetup(true);
    SetTargetFPS(0);
    EnableCursor();
    m_currentGameState = GameState::EditingMode;

    m_solarSystem.InitializeBodies();

    m_solarSystem.GetBodies()[0]->LoadBodyTexture("assets/texture.png");
    
#ifdef IMGUI_HAS_DOCK
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

}

void Game::ChangeGameState(GameState newState)
{
    m_currentGameState = newState;
}

void Game::Update()
{    
    // static bool lastCursorState = m_isCursorVisible;
    // if (lastCursorState != m_isCursorVisible) {
    //     lastCursorState = m_isCursorVisible;
    // }
    
    // m_inputManager.Update();

    if (!m_outputContext.pauseSimulation)
    {
        m_solarSystem.Update(GetFrameTime());
        m_solarSystem.ApplyGravity();
    }

    // if(m_currentGameState == GameState::CameraControl) m_cameraHandler.CameraUpdate();

    // if (m_isCursorVisible != lastCursorState)
    // {
    //     if (!m_isCursorVisible)
    //     {
    //         DisableCursor();
    //     }
    //     else
    //     {
    //         EnableCursor();
    //     }
    // }
}

void Game::Render()
{
    BeginDrawing();
        ClearBackground(DARKGRAY);

        BeginMode3D(*(m_cameraHandler.GetCamera()));

            DrawGrid(50, 1.0f);
            m_solarSystem.Draw();
            if (m_outputContext.wirebody != nullptr)
                DrawSphereWires(m_outputContext.wirebody->position, m_outputContext.wirebody->radius, 32, 32, BLACK);

        EndMode3D();

        rlImGuiBegin();
// Add docking to the ImGui viewport
#ifdef IMGUI_HAS_DOCK
		ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
#endif
        m_guiService.Render();

        rlImGuiEnd();
    EndDrawing();
}


void Game::Run()
{
     if (WindowShouldClose()) {
        m_isRunning = false;
        return;
    }
    Update();
    Render();
}

Game::~Game()
{
    rlImGuiShutdown();
    CloseWindow();
}
