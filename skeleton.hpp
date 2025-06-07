#pragma once

#include "enemy.hpp"
#include <string>
#include <iostream>

class Skeleton : public Enemy {
public:
    static std::string e_name;

    explicit Skeleton(int lvl);
    void show_informations() override;
};
