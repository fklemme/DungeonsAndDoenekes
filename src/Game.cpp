#include "Game.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "Enemy.hpp"
#include "Layers/Battle.hpp"
#include "utility/algorithm.hpp"

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

        // Update layer stack and view
        if (m_layers_update) {
            // Remove all layers marked for removal
            auto marked_for_removal = [](observer_ptr<Layer> ptr) { return ptr->m_marked_for_removal; };
            m_layers.erase(std::remove_if(m_layers.begin(), m_layers.end(), marked_for_removal), m_layers.end());

            // If layer stack is empty, close application
            if (m_layers.empty()) {
                m_main_window.close();
                return;
            }

            // Get a new layer view and update iterator to first drawing layer
            layer_view = std::vector<observer_ptr<Layer>>(m_layers.begin(), m_layers.end());
            auto bottom_layer_to_draw = [](observer_ptr<Layer> ptr) { return !ptr->m_render_underlying_layers; };
            layer_draw_begin = find_last_if(layer_view.begin(), layer_view.end(), bottom_layer_to_draw);
            // TOOD: Could be removed in the future:
            layer_draw_begin = layer_draw_begin == layer_view.end() ? layer_view.begin() : layer_draw_begin;

            m_layers_update = false;  // reset flag, so checks are not done on every frame

            std::cout << "Layers on stack: " << layer_view.size() << "\n";                                 // DEBUG!
            std::cout << "Layers to draw: " << std::distance(layer_draw_begin, layer_view.end()) << "\n";  // DEBUG!
        }

        // Draw stuff to the window
        auto elapsed_time = m_frame_timer.restart();
        m_main_window.clear();

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
