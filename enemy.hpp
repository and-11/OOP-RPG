#pragma once

#include "libraries.hpp"
#include "entity.hpp"

class Enemy : public Entity {
public:
    virtual void show_informations() = 0;

    Enemy(int level, int damage, int health, const std::string& name, int c_damage, int c_health);
};
