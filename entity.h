#pragma once

#include "libraryes.h"

class Potion;

class Entity{
private:
protected:
    int level,damage,health,current_health,current_damage;
    int coefficient_damage,coefficient_health;
    std::string name;
    bool player;
public:

    Entity(const Entity& other): name(other.name) {
        level = other.level;
        damage = other.damage;
        health = other.health;
        current_health = other.current_health;
        current_damage = other.current_damage;
        coefficient_damage = other.coefficient_damage;
        coefficient_health = other.coefficient_health;
        player = other.player;
    }

    Entity & operator=(const Entity& other) {
        level = other.level;
        damage = other.damage;
        health = other.health;
        current_health = other.current_health;
        current_damage = other.current_damage;
        coefficient_damage = other.coefficient_damage;
        coefficient_health = other.coefficient_health;
        player = other.player;
        name = "Cheap_coppy";
       return *this;
    }

    Entity()
    {
        current_health = 0;
        current_damage = 0;
        coefficient_damage = 0;
        coefficient_health = 0;
        level = damage = health = 0;
        name = "Forgotten";
        player = false;
    }
    Entity(const int level,const int damage,const int health,const std::string&name, const int c_damage, const int c_health )
    {
        player = false;
        this->level= level;
        this->damage = damage;
        this->health = health;
        this->name = name;
        this->coefficient_damage = c_damage;
        this->coefficient_health = c_health;
        current_damage = 0;
        current_health = 0;

    }
    virtual ~Entity() = default;
    [[nodiscard]] bool is_alive() const
    {
        return current_health > 0;
    }
    void Ready()
    {
        current_damage = damage + coefficient_damage*level;
        current_health = health + coefficient_health*level;
    }
    [[nodiscard]] std::string get_name() const
    {
        std::string ans,beg,end="\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        return beg+name+end;
    }
    [[nodiscard]] bool is_player() const
    {
        return player;
    }
    [[nodiscard]] int get_damage() const
    {
        return current_damage;
    }
    [[nodiscard]] std::string show_damage() const
    {
        std::string ans,beg,end="dmg\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        return beg+std::to_string(current_damage)+end;

    }
    void recive_damage(int value)
    {
        current_health -= value;
    }
    friend std::ostream & operator<<(std::ostream& os,const Entity & dude) {
        std::string ans,beg,end="\033[0m",dmg = " dmg:",hp =" hp:",lvl = " lvl:";
        if( dude.is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";

        os << beg+ dude.get_name() + lvl + std::to_string(dude.level) + dmg + std::to_string(dude.current_damage) + hp + std::to_string(dude.current_health) +end;
        return os;
    }   

    friend Potion;
};

