#include "Layers/Battle.hpp"

#include <SFML/Graphics/Text.hpp>
#include <sstream>

// For debugging
#include <iostream>
#include <memory>
#include "Layers/Test.hpp"

Battle::Battle(observer_ptr<const Player> player, observer_ptr<const Enemy> enemy)
    : m_player(player), m_enemy(enemy) {}

bool Battle::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            // Push Test layer
            std::cout << "A pressed -> Pushing Test layer!" << std::endl;
            m_game->emplace_layer<Test>();
            return true;
        }
    }

    return false;
}

void Battle::render(sf::RenderWindow& window, const sf::Time&) const {
    sf::Text player_name(m_player->name(), m_game->font());
    player_name.setPosition(600.0f, 0.0f);
    window.draw(player_name);

    std::stringstream phealth;
    phealth << m_player->health() << " / " << m_player->max_health();
    sf::Text player_health(phealth.str(), m_game->font());
    player_health.setPosition(600.0f, 50.0f);
    window.draw(player_health);

    sf::Text enemy_name(m_enemy->name(), m_game->font());
    enemy_name.setPosition(200.0f, 200.0f);
    window.draw(enemy_name);

    std::stringstream ehealth;
    ehealth << m_enemy->health() << " / " << m_enemy->max_health();
    sf::Text enemy_health(ehealth.str(), m_game->font());
    enemy_health.setPosition(200.0f, 250.0f);
    window.draw(enemy_health);
}