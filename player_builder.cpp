#include "player_builder.hpp"



Player_Builder::Player_Builder() {
    player = std::make_shared<Player>();
}
[[nodiscard]] std::shared_ptr<Player> Player_Builder::get_player() const {
    return player;
}

void Knight_Player_Builder::build_player()  {
    player->set_player( true );

    player->set_damage(4);
    player->set_health(10);

    std::string name = "Knight";
    player->set_name(name);

    player->set_coefficient_damage(2);
    player->set_coefficient_health(2);

    player->set_level(1);
    
    ///ANIMATION
    player->add_frames( 4, "knight_walk_frames" );
}

void Archer_Player_Builder::build_player()  {
    player->set_player( true );

    player->set_damage(10);
    player->set_health(6);

    std::string name = "Archer";
    player->set_name(name);

    player->set_coefficient_damage(2);
    player->set_coefficient_health(2);

    player->set_level(1);
    
    ///ANIMATION
    player->add_frames( 2, "archer_walk_frames" );
}

void Shield_Player_Builder::build_player() {
    player->set_player( true );

    player->set_damage(1);
    player->set_health(23);

    std::string name = "Shield";
    player->set_name(name);

    player->set_coefficient_damage(2);
    player->set_coefficient_health(2);

    player->set_level(1);
    
    ///ANIMATION
    player->add_frames( 6, "shield_walk_frames" );
}



void Player_Builder_Director::set_player_builder(std::shared_ptr<Player_Builder> player_builder) {
    this->player_builder = player_builder;
}

void Player_Builder_Director::build_player() {
    player_builder->build_player();
}

std::shared_ptr<Player> Player_Builder_Director::get_player() {
    return player_builder->get_player();
}


