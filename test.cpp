#include <iostream>
#include <typeinfo>

#include <vector>
int main() {


    int x = 5;
    std::cout << typeid(x).name() << std::endl;

    std::vector<int> a;
    std::cout << typeid( a.size() ).name() << std::endl;


}