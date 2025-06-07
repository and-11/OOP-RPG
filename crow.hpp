#pragma once

#include "enemy.hpp"
#include <string>
#include <iostream>

class Crow : public Enemy {
public:
    static std::string e_name;

    explicit Crow(int level);
    void show_informations() override;
};
