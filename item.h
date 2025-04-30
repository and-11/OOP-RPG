#pragma once

#include "entity.h"

class Item{
    std::string name;
public:
    virtual void description() = 0;
    virtual void use( Entity & dude ) = 0;
    std::string get_name() const
    {
        return "\033[36m"+name+"\033[0m";
    }
    Item() = default;
    Item(std::string s) : name{s}
    {} 
    virtual void print(std::ostream& os) const        ////            misto schema
    {
        os << name ;
    }
    friend std::ostream& operator<<(std::ostream& os,const Item& i)
    {
        os << "\033[36m" ;
        i.print(os);
        os << "\033[0m";
        return os;
    }    
};