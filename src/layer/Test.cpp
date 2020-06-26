#include "layer/Test.hpp"

Test::Test() : m_shape(100.0f) { m_shape.setFillColor(sf::Color::Green); }

bool Test::handle_event(const sf::Event&) { return false; }

bool Test::render(sf::RenderWindow& window, const sf::Time&) const {
    window.draw(m_shape);

    return false;
}