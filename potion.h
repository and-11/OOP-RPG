#pragma once

#include "libraryes.h"
#include "item.h"
#include "entity.h"


class Potion: public Item{
private:    
    int damage_increase,health_increase;
public:    
    void use( Entity & dude ) override
    {
        dude.current_damage += damage_increase;
        dude.current_health += health_increase;
        std::cout << get_name() << " used on " << dude.get_name() << "\n";
        std::cout << dude << "\n";
    }    
    Potion() : damage_increase{0} , health_increase{0} 
    {}
    Potion(std::string name,int damage_i,int health_i) : Item{name}, damage_increase{damage_i} , health_increase{health_i} 
    {}
    void description() override
    {
        std::cout << "A potion is an item that can be used on anny creature, either Hero or Enemy. Be careful how you use them...\n";
    }
    void print(std::ostream & os) const override 
    {
        os << get_name() << ": " << damage_increase << " damage output increase and " << health_increase <<" bonus health";
    }
};   