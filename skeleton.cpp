#include "skeleton.hpp"

std::string Skeleton::e_name = "SKELETON";

Skeleton::Skeleton(int level)
    : Enemy(level, 3, 1, e_name, 1, 1)
{
    /// ANIMATION
    this->add_frames(4, "skeleton_walk_frames");
}

void Skeleton::show_informations()
{
    std::cout << "The skeleton - He/She is really weak...\n";
}
