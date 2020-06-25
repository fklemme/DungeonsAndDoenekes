#include "Character.hpp"

#include <algorithm>

Character::Character(const std::string& name, int attack, int health)
    : m_name(name), m_attack(attack), m_health(health), m_max_health(health) {}

int Character::total_attack() const {
    int attack = m_attack;
    for (auto& item : m_inventory) {
        attack += item.attack();
    }
    return attack;
}

void Character::incur_damage(int attack) {
    for (auto& item : m_inventory) {
        attack -= item.armor();
    }
    m_health -= std::max(0, attack);
}
