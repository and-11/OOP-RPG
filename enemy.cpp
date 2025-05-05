#include "enemy.hpp"

Enemy::Enemy(int level, int damage, int health, const std::string& name, int c_damage, int c_health)
    : Entity(level, damage, health, name, c_damage, c_health) {}
