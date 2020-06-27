#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "Layers/Layer.hpp"

class Test : public Layer {
  public:
    Test();

    bool handle_event(const sf::Event&) override;
    void render(sf::RenderWindow&, const sf::Time&) const override;

  private:
    sf::CircleShape m_shape;
};