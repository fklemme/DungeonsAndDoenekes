#pragma once

#include <string>
#include <vector>
#include "Item.hpp"

class Character {
  public:
    Character(const std::string& name, int attack, int health);
    virtual ~Character() = default;

    // prevent slicing
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    inline const std::string& name() const { return m_name; }
    inline int health() const { return m_health; }
    inline int max_health() const { return m_max_health; }

    int attack() const;
    void deal_damage(int damage);

  protected:
    std::string m_name;
    int m_attack;  // base damage
    int m_health;  // hitpoints
    int m_max_health;
    std::vector<Item> m_inventory;
};