#include <iostream>

std::string pasSTRING = "3feb";

class Pereche{

private:
    std::string pas,usr;
    int skip;
public:
    friend std::istream& operator>>(std::istream& os,Pereche & x) {

        x.pas = pasSTRING;
        x.usr = "andrei";
        return os;
    }    
    void Afisare()
    {
        std::cout << usr << " " << pas << "\n";
    }
};


int main()
{
    Pereche xx;
    std::cin >>xx;
    xx.Afisare();
}