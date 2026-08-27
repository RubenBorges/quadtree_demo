#pragma once

// Creator:         Ruben Borges
// Creation Date:   31/8/2025
// Last Edit:       31/8/2025
// Description:     A simple C++ program that implements the SFML library.

#include <SFML/Graphics.hpp>
#include <quadtree.hpp>

// Recursively draw the quadtree regions and any stored nodes
void drawQuad(sf::RenderTarget& target, const Quad* quad, int depth = 0);
 
void seedRandomNodes(Quad& qt);

// A small helper that matches types
template<typename EventVariant, typename... Handlers>
void process_event(const EventVariant& event, Handlers&&... handlers) {
    // This executes the first lambda that accepts the active type inside the event
    (..., [&]() {
        if (const auto* ptr = event.template getIf<std::decay_t<decltype(handlers.target_type())>>()) { // Conceptually matches types
            // If SFML event holds this type, invoke the matching lambda
        }
    }());
}


/*
//   Define an action map of conditions -> consequences
//
// Inside your main loop (outside event polling, runs every frame):
//  
//  for (const auto& [condition, action] : continuous_actions) {
//       if (condition()) action();
//    }
*/
// 

// Define your flexible condition -> consequence structure

// Inside your Quad class:

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
