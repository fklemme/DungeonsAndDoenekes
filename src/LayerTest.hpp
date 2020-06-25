#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "Layer.hpp"

class LayerTest : public Layer {
  public:
    LayerTest();

    bool handle_event(const sf::Event&) override;
    bool render(sf::RenderWindow&, const sf::Time&) const override;

  private:
    sf::CircleShape m_shape;
};