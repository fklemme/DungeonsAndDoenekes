#include "Layers/Test.hpp"

#include <cstdlib>
#include <iostream>

Test::Test() : m_shape(100.0f) {
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(static_cast<float>(std::rand() % 600), static_cast<float>(std::rand() % 400));
}

bool Test::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::B) {
            // Pop Test layer
            std::cout << "B pressed -> Pop Test layer!" << std::endl;
            remove_this_layer();
            return true;
        }
    }

    return false;
}

void Test::render(sf::RenderWindow& window, const sf::Time&) const { window.draw(m_shape); }