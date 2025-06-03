#include "orc.hpp"

std::string Orc::e_name = "ORC";

Orc::Orc(int level)
    : Enemy(level, 3, 20, e_name, 1, 5)
{ 
    /// ANIMATION
    this->add_frames(4, "orc_walk_frames");
}

void Orc::show_informations()
{
    std::cout << "The orc - Has a lot of health.\n";
}
