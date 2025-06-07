#include "wolf.hpp"

std::string Wolf::e_name = "WOLF";

Wolf::Wolf(int level)
    : Enemy(level, 6, 9, e_name, 0, 2)
{
    /// ANIMATION
    this->add_frames( 4, "wolf_walk_frames");
}

void Wolf::show_informations()
{
    std::cout << "The wolf - A beast with sharp claws. It has high base damage but it does not scale with level.\n";
}
