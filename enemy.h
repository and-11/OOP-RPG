

#pragma once

#include "libraryes.h"

#include "entity.h"

class Enemy: public Entity {
public:
    virtual void show_informations() = 0;

    Enemy(const int level,const int damage,const int health,const std::string name, const int c_damage, const int c_health ) :
    Entity(level,damage,health,name,c_damage,c_health ) 
    {} 
};