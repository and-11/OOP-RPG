#pragma once

#include "item.hpp"
#include "entity.hpp"
#include <string>
#include <iostream>

class Potion : public Item {
private:
    int damage_increase;
    int health_increase;

public:
    Potion();
    Potion(const std::string& name, int damage_i, int health_i);

    void use(Entity& dude) override;
    void print(std::ostream& os) const override;
};
