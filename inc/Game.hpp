#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>

#include "Player.hpp"
#include "layer/Layer.hpp"

class Game {
  public:
    Game();

    void run();

    inline const sf::Font& font() const { return m_font; }

  private:
    sf::Font m_font;
    sf::RenderWindow m_main_window;
    sf::Clock m_frame_timer;
    std::vector<std::unique_ptr<Layer>> m_layers;

    std::unique_ptr<Player> m_player;
};