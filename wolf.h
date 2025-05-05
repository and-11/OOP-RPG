#pragma once

#include "libraryes.h"
#include "enemy.h"

class Wolf: public Enemy {
    private:
    
    public:
    static std::string e_name;

        void show_informations() override{
            std::cout<<"The wolf - A beast with sharp claws. It has high base damage but it does not scale with level.\n";
        }
        explicit Wolf(int level) : Enemy( level, 6 , 9 , e_name , 0 , 2)
        {}
};    

std::string Wolf::e_name = "WOLF";