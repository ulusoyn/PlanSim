#pragma once
#include "physics/CelestialBody.h"
#include <memory>

struct OutputContext {
    std::shared_ptr<CelestialBody> highlightedBody = nullptr;
    std::shared_ptr<CelestialBody> selectedBodyForGUI  = nullptr;

    bool showTrails = false;
    bool showVelocityVectors = false;
    bool showAccelerationVectors = false;
    bool showForceVectors = false;
    bool pauseSimulation = false;
};