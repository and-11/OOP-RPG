#pragma once

#include "libraries.hpp"
#include "enemy.hpp"

class Orc : public Enemy {
public:
    static std::string e_name;

    explicit Orc(int level);
    void show_informations() override;
};
