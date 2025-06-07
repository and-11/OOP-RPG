#pragma once

#include "enemy.hpp"
#include <string>
#include <iostream>

class Wolf : public Enemy {
public:
    static std::string e_name;

    explicit Wolf(int level);
    void show_informations() override;
};
