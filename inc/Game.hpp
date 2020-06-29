#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>
#include "Layers/Layer.hpp"
#include "Player.hpp"

class Game {
  public:
    Game();
    ~Game();

    void run();

    void push_layer(std::unique_ptr<Layer> layer);

    template <typename LayerType, typename... Args>
    void emplace_layer(Args&&... args) {
        push_layer(std::make_unique<LayerType>(std::forward<Args>(args)...));
    }

    inline void update_layers() { m_layers_update = true; }

    inline const sf::Font& font() const { return m_font; }

  private:
    sf::RenderWindow m_main_window;
    sf::Font m_font;

    std::vector<std::unique_ptr<Layer>> m_layers;
    bool m_layers_update = false;

    std::unique_ptr<Player> m_player;
};