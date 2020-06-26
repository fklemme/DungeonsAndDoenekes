#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

class Layer {
  public:
    Layer() = default;
    virtual ~Layer() = default;

    // Prevent slicing
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;

    // Called by Game class
    virtual bool handle_event(const sf::Event&) = 0;
    virtual bool render(sf::RenderWindow&, const sf::Time&) const = 0;
    inline bool render_underlying_layers() const { return m_render_underlying_layers; }
    inline bool remove_on_next_frame_update() const { return m_remove_on_next_frame_update; }

  protected:
    bool m_render_underlying_layers = true;
    bool m_remove_on_next_frame_update = false;
};