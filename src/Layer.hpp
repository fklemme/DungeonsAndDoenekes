#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class Layer {
  public:
    Layer() = default;
    virtual ~Layer() = default;

    // prevent slicing
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    virtual bool handle_event(const sf::Event&) = 0;
    virtual bool render(sf::RenderWindow&, const sf::Time&) const = 0;
    inline bool render_underlying_layers() const { return m_render_underlying_layers; }

  protected:
    bool m_render_underlying_layers = true;
};