#pragma once

#include "libraries.hpp"
#include "enemy.hpp"

class Goblin : public Enemy {
public:
    static std::string e_name;

    explicit Goblin(int level);
    void show_informations() override;
};
