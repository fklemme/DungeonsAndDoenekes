#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "Enemy.hpp"
#include "Game.hpp"
#include "Layer.hpp"
#include "Player.hpp"

class LayerBattle : public Layer {
  public:
    LayerBattle(Game* game, Player* player, Enemy* enemy);

    bool handle_event(const sf::Event&) override;
    bool render(sf::RenderWindow&, const sf::Time&) const override;

  private:
    Game* m_game;
    Player* m_player;
    Enemy* m_enemy;
};