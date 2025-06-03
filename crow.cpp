#include "crow.hpp"

std::string Crow::e_name = "CROW";

Crow::Crow(int level): Enemy(level, 1, 1, e_name, 0, 1) {
///ANIMATION
    this->add_frames( 4, "crow_walk_frames" );       
}

void Crow::show_informations() {
    std::cout << "The Crow - why is the crow here...\n";
}