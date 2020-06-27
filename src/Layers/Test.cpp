#include "Layers/Test.hpp"

#include <iostream>

Test::Test() : m_shape(100.0f) { m_shape.setFillColor(sf::Color::Green); }

bool Test::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::B) {
            // Pop Test layer
            std::cout << "B pressed -> Pop Test layer!" << std::endl;
            remove_on_next_frame_update();
            return true;
        }
    }

    return false;
}

void Test::render(sf::RenderWindow& window, const sf::Time&) const {
    window.draw(m_shape);
}