#include "Game.hpp"

#include <stdexcept>

#include "Enemy.hpp"
#include "Layers/Battle.hpp"

Game::Game() : m_main_window(sf::VideoMode(800, 600), "Dungeons And Doenekes") {
    // Load font
    const std::string font_path = "res/dejavu-fonts/DejaVuSans.ttf";
    if (!m_font.loadFromFile(font_path)) throw std::runtime_error("Could not load " + font_path);

    // Create player
    m_player = std::make_unique<Player>("Player", 5, 100);
}

void Game::run() {
    // TODO: Testing!
    Enemy enemy1("Enemy 1", 5, 25);
    emplace_layer<Battle>(m_player.get(), &enemy1);

    // Stack of layers must not be changed while iterating through it.
    // Thus we iterate over a copy holding references.
    auto layer_view = std::vector<observer_ptr<Layer>>(m_layers.begin(), m_layers.end());
    auto layer_draw_begin = layer_view.begin();

    while (m_main_window.isOpen()) {
        // Handle events, or forward to layers
        sf::Event event;
        while (m_main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_main_window.close();  // TODO: Move to main menu
            } else {
                // Dispatch event, top to bottom, until some layer returns true.
                for (auto it = layer_view.rbegin(); it != layer_view.rend(); ++it) {
                    if ((*it)->handle_event(event)) break;
                }
            }
        }

        // Check status and update layer_view if needed.
        if (m_layers_update) {
			// TODO: Update layers...
            // Get a new layer view
            layer_view = std::vector<observer_ptr<Layer>>(m_layers.begin(), m_layers.end());
            layer_draw_begin = layer_view.begin();        // TODO: set begin correctly
            if (m_layers.empty()) m_main_window.close();  // TODO: Is this the right place?
            m_layers_update = false;                      // reset flag
        }

        // Draw stuff to the window
        auto elapsed_time = m_frame_timer.restart();
        m_main_window.clear();

        // Find the last layer that is not showing (further) underlying layers
        // auto it = m_layers.end();
        // while (it != m_layers.begin() && (*--it)->render_underlying_layers());

        // Dispatch rendering, bottom to top
        for (auto it = layer_draw_begin; it != layer_view.end(); ++it) (*it)->render(m_main_window, elapsed_time);

        m_main_window.display();  // swap buffers
    }
}

void Game::push_layer(std::unique_ptr<Layer> layer) {
    m_layers.push_back(std::move(layer));
    m_layers.back()->m_game.reset(this);  // set back reference
    update_layers();
}
