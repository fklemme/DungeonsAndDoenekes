#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "Enemy.hpp"
#include "Game.hpp"
#include "Layers/Layer.hpp"
#include "Player.hpp"
#include "utility/observer_ptr.hpp"

class Battle : public Layer {
  public:
    Battle(observer_ptr<const Player> player, observer_ptr<const Enemy> enemy);

    bool handle_event(const sf::Event&) override;
    void render(sf::RenderWindow&, const sf::Time&) const override;

  private:
    observer_ptr<const Player> m_player;
    observer_ptr<const Enemy> m_enemy;
};