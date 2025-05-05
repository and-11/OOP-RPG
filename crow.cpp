#include "crow.hpp"

std::string Crow::e_name = "CROW";

Crow::Crow(int level)
    : Enemy(level, 1, 1, e_name, 0, 1) {}

void Crow::show_informations() {
    std::cout << "The Crow - why is the crow here...\n";
}
