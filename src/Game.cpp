#include "Game.hpp"

#include "TestLayer.hpp"

Game::Game() : m_main_window(sf::VideoMode(800, 600), "Dungeons And Doenekes") {
    m_layers.push_back(std::make_unique<TestLayer>());
}

void Game::run() {
    while (m_main_window.isOpen()) {
        sf::Event event;
        while (m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_main_window.close();  // TODO: Move to main menu
            } else {
                // Dispatch event handling, top-down
                for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
                    if ((*it)->handle_event(event)) break;
                }
            }
        }

        auto elapsed_time = m_frame_timer.restart();
        m_main_window.clear();

        // Find the last layer that is not showing (further) underlying layers
        auto it = m_layers.end();
        while (it != m_layers.begin() && (*--it)->render_underlying_layers())
            ;

        // Dispatch rendering, bottom-up
        for (; it != m_layers.end(); ++it) {
            if ((*it)->render(m_main_window, elapsed_time)) break;
        }

        m_main_window.display();
    }
}