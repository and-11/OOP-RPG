#pragma once

#include "libraryes.h"
#include "exception.h"

void clear_window()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/macOS
    #endif
}

int getRandomNumber() {
    
    int low = 1, high = INT_MAX;
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}

int get_numeric_input()
{
    int option;
    while( 1 )
    {
        std::cin >> option;
        try{

            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(10000, '\n'); // discard invalid input
                throw Input_NAN();
            }     //// daca coteste litere da fail si nu mai colaboreaza
            break;
        }
        catch( MyException&e )
        {
            std::cout << e.what() << "\n";
        }
    }
    return option;         
}