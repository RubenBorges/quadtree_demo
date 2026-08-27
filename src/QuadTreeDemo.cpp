// --- QuadTreeDemo.cpp ---
#include <Config.hpp>
#include <draw.hpp>
#include <quadtree.hpp>
#include <ZenityDialog.hpp>
#include <CameraController.hpp>  // 🌟 MAKE SURE THIS ENDS IN .hpp, NOT .cpp!
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <optional>

////////////////////////////////////////////////////////////
///         Entry point of application                   ///
////////////////////////////////////////////////////////////
int main(){
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed randomness

    sf::RenderWindow window(
        sf::VideoMode({ Config::WindowWidth, Config::WindowHeight }),
        "Quadtree Demo",
        sf::Style::Titlebar | sf::Style::Close,
        sf::State::Windowed,
        sf::ContextSettings{ 0 /* depthBits */, 8 /* stencilBits */ }
    );

    //Quad qt(Point(0, 0), Point(Config::WindowWidth, Config::WindowHeight));    // Create quadtree covering the full window bounds
    Quad qt(Point(-50000, -50000), Point(50000, 50000));    // Create quadtree covering a LARGE virtual canvas, beyond window bounds
    sf::View camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(Config::WindowWidth), static_cast<float>(Config::WindowHeight)}));
    CameraController cameraController(camera);
    
    // Track the cursor's translated world-space coordinate
    sf::Vector2f worldMousePos{ 0.f, 0.f };
       
    // =========================================================================
    // 🕹️ EVENT HANDLER LAMBDAS
    // =========================================================================
    
    auto handleKeyPress = [&](const sf::Event::KeyPressed& key) {
        if (key.scancode == sf::Keyboard::Scan::Escape) {
            if (ZenityDialog::question("Exit", "Would you like to exit?")) window.close();
        }
    };

    auto handleMouseMove = [&](const sf::Event::MouseMoved& mouseMove) {
        sf::Vector2i pixelPos = { mouseMove.position.x, mouseMove.position.y };
        worldMousePos = window.mapPixelToCoords(pixelPos, camera);
    };

    auto handleMousePress = [&](const sf::Event::MouseButtonPressed& mouse) {
        if (mouse.button == sf::Mouse::Button::Left) {
            int targetX = static_cast<int>(worldMousePos.x);
            int targetY = static_cast<int>(worldMousePos.y);
            static int nextId = 1000;
            qt.insert(new Node(Point(targetX, targetY), nextId++));
        }
    };

    // =========================================================================
    // 🎨 RENDERING ENGINE LAMBDAS
    // =========================================================================

    // Lambda to draw the entire Quadtree structure
    auto renderQuadTree = [&]() {
        qt.traverse([&window](const Quad* currentSubTree) {
            // Draw the boundaries for the current sub-quadrant
            sf::RectangleShape box;
            auto tl = currentSubTree->getTopLeft();
            auto br = currentSubTree->getBotRight();
            
            box.setPosition({ static_cast<float>(tl.x), static_cast<float>(tl.y) });
            box.setSize({ static_cast<float>(br.x - tl.x), static_cast<float>(br.y - tl.y) });
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineColor(sf::Color(100, 100, 100)); // Dim Gray outlines
            box.setOutlineThickness(1.0f);
            window.draw(box);

            // Draw all individual points residing inside this quadrant leaf
            for (const auto* node : currentSubTree->getNodes()) {
                sf::CircleShape point(2.0f);
                point.setFillColor(sf::Color::Green);
                point.setPosition({ static_cast<float>(node->pos.x - 2), static_cast<float>(node->pos.y - 2) });
                window.draw(point);
            }
        });
    };

    // Lambda to draw the virtual world-space crosshair lines
    auto renderCrosshair = [&]() {
        float crosshairSize = 15.0f; 
        sf::Color crosshairColor = sf::Color::Red; 

        sf::Vertex lineH[] = {
            sf::Vertex({ worldMousePos.x - crosshairSize, worldMousePos.y }, crosshairColor),
            sf::Vertex({ worldMousePos.x + crosshairSize, worldMousePos.y }, crosshairColor)
        };
        sf::Vertex lineV[] = {
            sf::Vertex({ worldMousePos.x, worldMousePos.y - crosshairSize }, crosshairColor),
            sf::Vertex({ worldMousePos.x, worldMousePos.y + crosshairSize }, crosshairColor)
        };

        window.draw(lineH, 2, sf::PrimitiveType::Lines);
        window.draw(lineV, 2, sf::PrimitiveType::Lines);
    };

    // =========================================================================
    // 🔄 MAIN SIMULATION LOOP (Ultra-Clean Version)
    // =========================================================================
  // 🌟 1. Create a clock right before entering the loop
    sf::Clock deltaClock;

    while (window.isOpen()) {
        // 🌟 2. Restart the clock each frame to capture seconds elapsed (Delta Time)
        float dt = deltaClock.restart().asSeconds();

        // Process Input and Events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { window.close(); }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())          handleKeyPress(*key);
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) handleMousePress(*mouse);
            else if (const auto* move = event->getIf<sf::Event::MouseMoved>())         handleMouseMove(*move);
        }

        // 🌟 3. PASS THE DELTA TIME VALUE TO YOUR CAMERA CONTROLLER
        cameraController.update(dt);
        
        // Render Output Framework
        window.clear(sf::Color(25, 25, 25));
        window.setView(camera); 
        
        renderQuadTree();   
        renderCrosshair();  

        window.display();
    }

    return EXIT_SUCCESS;
}
