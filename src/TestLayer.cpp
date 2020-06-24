#include "TestLayer.hpp"

TestLayer::TestLayer() : m_shape(100.0f) { m_shape.setFillColor(sf::Color::Green); }

bool TestLayer::handle_event(const sf::Event&) { return false; }

bool TestLayer::render(sf::RenderWindow& window, const sf::Time&) const {
    window.draw(m_shape);
    return false;
}