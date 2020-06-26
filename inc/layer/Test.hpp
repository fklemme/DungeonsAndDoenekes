#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "layer/Layer.hpp"

class Test : public Layer {
  public:
    Test();

    bool handle_event(const sf::Event&) override;
    bool render(sf::RenderWindow&, const sf::Time&) const override;

  private:
    sf::CircleShape m_shape;
};