#pragma once

#include "libraryes.h"
#include "enemy.h"

class Orc: public Enemy {
    private:
    
    public:
    static std::string e_name;

        void show_informations() override{
            std::cout<<"The orc - Has a lot of health.\n";
        }
        explicit Orc(int level) : Enemy( level, 3 , 20 , e_name , 1 , 5 )
        {}
};    

std::string Orc::e_name = "ORC";