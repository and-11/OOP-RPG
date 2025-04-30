#pragma once

#include "libraryes.h"
#include "item.h"
#include "potion.h"


class Potion;

class Entity{
private:
protected:
    int level,damage,health,current_health,current_damage;
    int coeficient_damage,coeficient_health;
    std::string name;
    bool player;
public:

    Entity(const Entity& other) {
        level = other.level;
        damage = other.damage;
        health = other.health;
        current_health = other.current_health;
        current_damage = other.current_damage;
        player = other.player;
        name = other.name;
    }

    Entity & operator=(const Entity& other) {
        level = other.level;
        damage = other.damage;
        health = other.health;
        current_health = other.current_health;
        current_damage = other.current_damage;
        player = other.player;
        name = other.name;
       return *this;
    }

    ~Entity() = default ; 




    Entity()
    {
        level = damage = health = 0;
        name = "Forgotten";
        player =0;
    }
    Entity(const int level,const int damage,const int health,const std::string name, const int c_damage, const int c_health )
    {
        player =0;
        this->level= level;
        this->damage = damage;
        this->health = health;
        this->name = name;
        this->coeficient_damage = c_damage;
        this->coeficient_health = c_health;
    }
    virtual ~Entity() = default;
    bool is_alive() 
    {
        return current_health > 0;
    }
    void Ready()
    {
        current_damage = damage + coeficient_damage*level;
        current_health = health + coeficient_health*level;
    }
    std::string get_name() const
    {
        std::string ans,beg,end="\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        ans = beg+name+end;
        return ans;
    }
    bool is_player() const
    {
        return player;
    }
    int get_damage()
    {
        return current_damage;
    }
    std::string show_damage()
    {
        std::string ans,beg,end="dmg\033[0m";
        if( is_player() )
            beg = "\033[32m";
        else 
            beg = "\033[31m";
        ans = beg+std::to_string(current_damage)+end;
        return ans;
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

        ans = beg+ dude.get_name() + lvl + std::to_string(dude.level) + dmg + std::to_string(dude.current_damage) + hp + std::to_string(dude.current_health) +end;
        os << ans;      /// fix
        return os;
    }   

    friend Potion;
};

