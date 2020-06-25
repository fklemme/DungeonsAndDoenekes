#pragma once

#include "Character.hpp"

class Player : public Character {
  public:
    inline Player(const std::string& name, int attack, int health) : Character(name, attack, health) {}
};