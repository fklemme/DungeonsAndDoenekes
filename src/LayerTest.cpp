#include "LayerTest.hpp"

LayerTest::LayerTest() : m_shape(100.0f) { m_shape.setFillColor(sf::Color::Green); }

bool LayerTest::handle_event(const sf::Event&) { return false; }

bool LayerTest::render(sf::RenderWindow& window, const sf::Time&) const {
    window.draw(m_shape);

    return false;
}