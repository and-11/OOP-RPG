#pragma once

#include "libraryes.h"
#include "enemy.h"

class Skeleton: public Enemy {
    private:
    
    public:
    static std::string e_name;

        void show_informations() override{
            std::cout<<"The skeleton - He/She is realy weak...\n";
        }
        explicit Skeleton(int level) : Enemy( level, 3 , 1 , e_name , 1 , 1)
        {}
};    

std::string Skeleton::e_name = "SKELETON";