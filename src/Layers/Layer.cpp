#include "Layers/Layer.hpp"

#include "Game.hpp"

void Layer::remove_this_layer() {
    m_marked_for_removal = true;
    m_game->update_layers();
}