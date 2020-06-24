#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>
#include <vector>

#include "Layer.hpp"

class Game {
   public:
    Game();

    void run();

   private:
    sf::RenderWindow m_main_window;
    sf::Clock m_frame_timer;
    std::vector<std::unique_ptr<Layer>> m_layers;
};