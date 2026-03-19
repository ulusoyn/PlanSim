// GUIService.h

#include "imgui.h"
#include "raylib.h"
#include "physics/CelestialBody.h"
#include "physics/SolarSystem.h"
#include "ui/OutputContext.h"
#include "core/GameServices.h"


class GUIService {
public:
    GUIService(OutputContext& output, GameServices& services)
        : m_output(output), m_services(services), m_showDemoWindow(true) {}
    
    void Render() {
        RenderInspector();
        RenderControls();
        RenderDebugInfo();
    }

private:
    void RenderInspector() {
        ImGui::Begin("Celestial Body Inspector");
        
        if (m_output.highlightedBody != nullptr) {
            auto& body = m_output.highlightedBody;
            
            ImGui::Text("Name: %s", body->GetName().c_str());
            
            Vector3 pos = body->GetPosition();
            if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) {
                body->SetPosition(pos);
            }
            
            Vector3 vel = body->GetVelocity();
            ImGui::DragFloat3("Velocity", &vel.x, 0.1f);
            
            float mass = body->GetMass();
            ImGui::Text("Mass: %.2e kg", mass);
            
            if (ImGui::Button("Deselect")) {
                m_output.highlightedBody = nullptr;
            }
        } else {
            ImGui::Text("No body selected");
            ImGui::TextDisabled("Click on a celestial body to inspect");
        }
        
        ImGui::End();

        // show ImGui Content
        bool open = true;
        ImGui::ShowDemoWindow(&open);

                // show a simple menu bar
                
        // include/ui/GUIService.h — RenderInspector() içinde

            if (ImGui::BeginMainMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Quit")) {}  
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Window"))
                {
                    if (ImGui::MenuItem("Demo Window", nullptr, m_showDemoWindow))
                        m_showDemoWindow = !m_showDemoWindow;
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();  
            }
        // show some windows
    
        if (m_showDemoWindow)
            ImGui::ShowDemoWindow(&m_showDemoWindow);

    }
    
    void RenderControls() {
        ImGui::Begin("Simulation Controls");
        
        ImGui::Checkbox("Show Trails", &m_output.showTrails);
        ImGui::Checkbox("Show Velocity Vectors", &m_output.showVelocityVectors);
        ImGui::Checkbox("Pause Simulation", &m_output.pauseSimulation);
        
        if (ImGui::Button("Reset Camera")) {
            // Trigger camera reset
        }
        
        ImGui::End();
    }
    
    void RenderDebugInfo() {
        ImGui::Begin("Debug Info");
        
        ImGui::Text("FPS: %d", GetFPS());
        ImGui::Text("Bodies: %zu", m_services.solarSystem->GetBodies().size());
        
        Vector3 camPos = m_services.camera->position;
        ImGui::Text("Camera: (%.1f, %.1f, %.1f)", camPos.x, camPos.y, camPos.z);
        
        ImGui::End();
    }

private:
    OutputContext& m_output;
    GameServices& m_services;
    bool m_showDemoWindow;
};