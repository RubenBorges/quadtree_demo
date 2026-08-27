// Creator:         Ruben Borges
// Creation Date:   31/8/2025
// Last Edit:       31/8/2025
// Description:     A simple C++ program that implements the SFML library.

#include <SFML/Graphics.hpp>
#include <quadtree.hpp>
#include <cstdlib>
#include <Config.hpp>
// Recursively draw the quadtree regions and any stored nodes
// void drawQuad(sf::RenderTarget& target, const Quad* quad, int depth) {
//     if (!quad) return;

//     Point tl = quad->getTopLeft();
//     Point br = quad->getBotRight();

//     sf::RectangleShape region;
//     region.setPosition(sf::Vector2f(static_cast<float>(tl.x), static_cast<float>(tl.y)));
//     region.setSize(sf::Vector2f(static_cast<float>(br.x - tl.x), static_cast<float>(br.y - tl.y)));
//     region.setFillColor(sf::Color::Transparent);
//     region.setOutlineColor(sf::Color(100 + (depth * 30) % 155, 255 - (depth * 30) % 255, 150));
//     region.setOutlineThickness(1.0f);
//     target.draw(region);

//     // Draw all nodes stored in a leaf (a quad without children)
//     if (!quad->getTopLeftTree() && !quad->getTopRightTree() &&
//         !quad->getBotLeftTree() && !quad->getBotRightTree()) {
//         for (const Node* n : quad->getNodes()) {
//             sf::CircleShape dot(3);
//             dot.setFillColor(sf::Color::Red);
//             dot.setPosition(sf::Vector2f(static_cast<float>(n->pos.x - 3), static_cast<float>(n->pos.y - 3)));
//             target.draw(dot);
//         }
//     }

//     drawQuad(target, quad->getTopLeftTree(), depth + 1);
//     drawQuad(target, quad->getTopRightTree(), depth + 1);
//     drawQuad(target, quad->getBotLeftTree(), depth + 1);
//     drawQuad(target, quad->getBotRightTree(), depth + 1);
// }
void drawQuadTree(sf::RenderTarget& target, const Quad& qt) {
    // Traverses every sub-quadrant and draws its bounding boxes and containing nodes
    qt.traverse([&target](const Quad* currentSubTree) {
        // Construct the geometry box for this quadrant boundary
        sf::RectangleShape box;
        auto tl = currentSubTree->getTopLeft();
        auto br = currentSubTree->getBotRight();
        box.setPosition({ static_cast<float>(tl.x), static_cast<float>(tl.y) });
        box.setSize({ static_cast<float>(br.x - tl.x), static_cast<float>(br.y - tl.y) });
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineColor(sf::Color(100, 100, 100)); // Dim Gray borders
        box.setOutlineThickness(1.0f);
        target.draw(box);

        // Draw all individual nodes nested directly inside this leaf
        for (const auto* node : currentSubTree->getNodes()) {
            sf::CircleShape point(2.0f);
            point.setFillColor(sf::Color::Green);
            point.setPosition({ static_cast<float>(node->pos.x - 2), static_cast<float>(node->pos.y - 2) });
            target.draw(point);
        }
    });
}

//Insert some random nodes initially
void seedRandomNodes(Quad& qt){
   for (int i = 0; i < 100; ++i) {
       int x = std::rand() % Config::WindowWidth;
       int y = std::rand() % Config::WindowHeight;
       qt.insert(new Node(Point(x, y), i));
   }
}

// ////////////////////////////////////////////////////////////
// ///         Entry point of application                   ///
// ////////////////////////////////////////////////////////////
// int main()
// {
//     // Seed randomness
//     std::srand(static_cast<unsigned int>(std::time(nullptr)));

//     // Create the window of the application with a stencil buffer (SFML 3 API)
//     sf::RenderWindow window(
//         sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
//         "Quadtree Demo",
//         sf::Style::Titlebar | sf::Style::Close,
//         sf::State::Windowed,
//         sf::ContextSettings{ 0 /* depthBits */, 8 /* stencilBits */ }
//     );

//     // Create quadtree covering the full window bounds
//     Quad qt(Point(0, 0), Point(WINDOW_WIDTH, WINDOW_HEIGHT));

//     // Insert some random nodes initially
//  //   for (int i = 0; i < 100; ++i) {
//   //      int x = std::rand() % WINDOW_WIDTH;
//    //     int y = std::rand() % WINDOW_HEIGHT;
//   //      qt.insert(new Node(Point(x, y), i));
//   //  }

//     while (window.isOpen()) {
//         while (const std::optional<sf::Event> event = window.pollEvent()) {
//             if (event->is<sf::Event::Closed>()) {
//                 window.close();
//                 break;
//             }
//             if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
//                 if (key->scancode == sf::Keyboard::Scan::Escape) {
//                     if (ZenityDialog::question("Exit","Would you like to exit?"))window.close();
//                     break;
//                 }
//             }
//             if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>(); mouse && mouse->button == sf::Mouse::Button::Left) {
//                     const auto pos = sf::Mouse::getPosition(window);
//                     // Clamp to window bounds just in case
//                     int x = std::max(0, std::min(static_cast<int>(pos.x), WINDOW_WIDTH));
//                     int y = std::max(0, std::min(static_cast<int>(pos.y), WINDOW_HEIGHT));
//                     static int nextId = 1000;
//                     qt.insert(new Node(Point(x, y), nextId++));
//             }
//         }

//         window.clear(sf::Color(25, 25, 25));
//         drawQuad(window, &qt);
//         window.display();
//     }

//     return EXIT_SUCCESS;
// }
