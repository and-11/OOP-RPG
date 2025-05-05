#pragma once

#include "libraryes.h"
#include "enemy.h"

class Goblin : public Enemy {
public:
    static std::string e_name;

    explicit Goblin(int level);
    void show_informations() override;
};
