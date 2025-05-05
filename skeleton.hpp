#pragma once

#include "enemy.hpp"
#include <string>
#include <iostream>

class Skeleton : public Enemy {
public:
    static std::string e_name;

    explicit Skeleton(int level);
    void show_informations() override;
};
