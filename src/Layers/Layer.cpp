#include "Layers/Layer.hpp"

#include "Game.hpp"

void Layer:: remove_on_next_frame_update() {
    m_remove_on_next_frame_update = true;
    m_game->update_layers();
}