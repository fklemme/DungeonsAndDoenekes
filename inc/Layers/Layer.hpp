#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "utility/observer_ptr.hpp"

class Game;  // forward declaration

class Layer {
    friend class Game;

  public:
    Layer() = default;
    virtual ~Layer() = default;

    // Prevent slicing
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    // The following functions are all called by Game class

    // Handle event. If the event has handled by this layer, return true.
    // If false is returned, underlying layers will get the chance to handle the event.
    virtual bool handle_event(const sf::Event&) = 0;

    // Render layer.
    virtual void render(sf::RenderWindow&, const sf::Time&) const = 0;

  protected:
    observer_ptr<Game> m_game;  // Will be set when pushed to game.
    bool m_render_underlying_layers = true;
    void remove_this_layer();

  private:
    bool m_marked_for_removal = false;
};