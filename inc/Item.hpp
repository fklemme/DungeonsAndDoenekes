#pragma once

class Item {
  public:
    inline Item(int attack, int armor) : m_attack(attack), m_armor(armor) {}

    inline int attack() const { return m_attack; }
    inline int armor() const { return m_armor; }

  private:
    int m_attack;
    int m_armor;
};