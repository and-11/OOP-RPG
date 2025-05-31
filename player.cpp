#include "player.hpp"

Player::Player() {
    // std::cerr << "You did not set stats for a Player!!\n";
}

Player::Player(int damage, int health, const std::string& name, int c_damage, int c_health)
    : Entity(1, damage, health, name, c_damage, c_health) {
    player = true;
}

