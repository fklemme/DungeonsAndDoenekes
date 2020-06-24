#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>
#include "Layer.hpp"

class Game {
  public:
    Game();

    void run();

    inline const sf::Font& font() const { return m_font; }

  private:
    sf::RenderWindow m_main_window;
    sf::Clock m_frame_timer;
    std::vector<std::unique_ptr<Layer>> m_layers;

    sf::Font m_font;
};