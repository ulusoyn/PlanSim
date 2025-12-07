#pragma once
#include <memory>

class CelestialBody;

struct WireFrameBody
{
    float radius;
    Vector3 position;
    Color color;

    WireFrameBody(){}
    WireFrameBody(float radius, Vector3 position, Color color)
        : radius(radius), position(position), color(color){}
};

struct OutputContext {
    std::shared_ptr<WireFrameBody> wirebody = nullptr;
    std::shared_ptr<CelestialBody> highlightedBody = nullptr;
    std::shared_ptr<CelestialBody> selectedBodyForGUI  = nullptr;

    bool showTrails = false;
    bool showVelocityVectors = false;
    bool showAccelerationVectors = false;
    bool showForceVectors = false;
    bool pauseSimulation = false;

    OutputContext() = default;
};