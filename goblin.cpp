#include "goblin.hpp"

std::string Goblin::e_name = "GOBLIN";

Goblin::Goblin(int level)
    : Enemy(level, 4, 5, e_name, 3, 1)
{
    /// ANIMATION
    this->add_frames(4, "goblin_walk_frames");
}

void Goblin::show_informations()
{
    std::cout << "The goblin - we don't know much about the goblin. He is a green dude that is low in health but has high damage! Be careful, the Goblin's damage scales well with his level.\n";
}
