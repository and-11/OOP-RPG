#pragma once
#include "functions.hpp"


template <typename T>   /// int float....
class random_cls{
public:

    random_cls() = default;
    T get_random_number()
    {
        T x =1;
        return x* getRandomNumber() / 2;
    }

};