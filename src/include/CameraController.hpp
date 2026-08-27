#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <functional>

class CameraController {
private:
    sf::View& m_camera;
    std::vector<std::pair<std::function<bool()>, std::function<void()>>> m_continuousActions;

    // Speeds are now defined as "units per second" rather than "units per frame"
    float m_moveSpeed{ 400.0f };  // Panning speed (pixels/second)
    float m_zoomSpeed{ 1.5f };    // Zoom scaling rate

    void setupDefaultBindings(float deltaTime); // 🌟 Now accepts deltaTime

public:
    explicit CameraController(sf::View& targetCamera);

    // 🌟 Pass the elapsed frame time here
    void update(float deltaTime);

    void setMoveSpeed(float speed);
};
