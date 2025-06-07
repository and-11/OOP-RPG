#pragma once

#include "entity.hpp"
#include <string>
#include <iostream>

class Player : public Entity {
public:
    Player();  // default constructor
    Player(int damage, int health, const std::string& name, int c_damage, int c_health);
};
