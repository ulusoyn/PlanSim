#pragma once
#include "imgui.h"

class GUIService {
private:

public:
    GUIService() = default;

    void RenderGUI(class GameServices& services, class OutputContext& output);


};