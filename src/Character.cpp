#include "Character.hpp"

#include <algorithm>

Character::Character(const std::string& name, int attack, int health)
    : m_name(name), m_attack(attack), m_health(health), m_max_health(health) {}

int Character::attack() const {
    int total_damage = m_attack;
    for (auto& item : m_inventory) {
        total_damage += item.attack();
    }
    return total_damage;
}

void Character::deal_damage(int attack) {
    for (auto& item : m_inventory) {
        attack -= item.armor();
    }
    m_health -= std::max(0, attack);
}
