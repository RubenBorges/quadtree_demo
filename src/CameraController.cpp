#include "CameraController.hpp"

CameraController::CameraController(sf::View& targetCamera) 
    : m_camera(targetCamera) 
{
    // Initialize with a default placeholder delta time
    setupDefaultBindings(0.016f);
}

void CameraController::setupDefaultBindings(float deltaTime) {
    // Multiply steps by deltaTime to achieve frame-rate independence
    float travelDistance = m_moveSpeed * deltaTime;
    
    // For smooth exponential zooming, we scale the factor exponentially by deltaTime
    float zoomInFactor = std::pow(1.0f / m_zoomSpeed, deltaTime);
    float zoomOutFactor = std::pow(m_zoomSpeed, deltaTime);

    m_continuousActions = {
        // --- WASD Controls ---
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W); }, [this, travelDistance](){ m_camera.move({0.f, -travelDistance}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A); }, [this, travelDistance](){ m_camera.move({-travelDistance, 0.f}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S); }, [this, travelDistance](){ m_camera.move({0.f, travelDistance}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D); }, [this, travelDistance](){ m_camera.move({travelDistance, 0.f}); } },

        // --- Arrow Key Controls ---
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up); },    [this, travelDistance](){ m_camera.move({0.f, -travelDistance}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down); },  [this, travelDistance](){ m_camera.move({0.f, travelDistance}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left); },  [this, travelDistance](){ m_camera.move({-travelDistance, 0.f}); } },
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right); }, [this, travelDistance](){ m_camera.move({travelDistance, 0.f}); } },

        // --- Zoom Controls ---
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q); },        [this, zoomInFactor](){ m_camera.zoom(zoomInFactor); } }, 
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E); },        [this, zoomOutFactor](){ m_camera.zoom(zoomOutFactor); } }, 
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageUp); },    [this, zoomInFactor](){ m_camera.zoom(zoomInFactor); } }, 
        { [](){ return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown); },  [this, zoomOutFactor](){ m_camera.zoom(zoomOutFactor); } }  
    };
}

void CameraController::update(float deltaTime) {
    // Rebind each frame with the latest precise deltaTime
    setupDefaultBindings(deltaTime);

    for (const auto& [condition, action] : m_continuousActions) {
        if (condition()) {
            action();
        }
    }
}

void CameraController::setMoveSpeed(float speed) {
    m_moveSpeed = speed;
}
