#pragma once

#include "Character.hpp"

class Enemy : public Character {
  public:
    inline Enemy(const std::string& name, int attack, int health) : Character(name, attack, health) {}
};