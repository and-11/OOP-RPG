#pragma once

#include "libraryes.h"

#include "entity.h"



class Player: public Entity{
    private:    
    public:
        Player()
        {
            std::cerr << "You did not set stats for a Player!!\n";
        }    
        Player(int damage,int health,std::string name,int c_damage,int c_health) : 
            Entity( 1, damage, health, name , c_damage, c_health )
        {
            player =1;
        }    

    };    
    