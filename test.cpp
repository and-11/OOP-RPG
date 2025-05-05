#include <iostream>
#include <typeinfo>

#include <vector>


class A {
public:
   virtual void Afis() {
        std::cout << " A ";
    }
};class B:public A {
public:
    void Afis() {
        std::cout << " Bs ";
    }
};class C:public B {
public:
    void Afis() {
        std::cout << " C ";
    }
};


int main() {
    A *x = new C;
    x->Afis();

}