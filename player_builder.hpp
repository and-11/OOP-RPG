#pragma once

#include "functions.hpp"
#include "player.hpp"

class Player_Builder
{
protected:
    std::shared_ptr<Player> player;
public:
    Player_Builder() {
        player = std::make_shared<Player>();
    }
    virtual void build_player() = 0;

    [[nodiscard]] std::shared_ptr<Player> get_player() const {
        return player;
    }
    virtual ~Player_Builder() = default;
};

class Knight_Player_Builder : public Player_Builder {
public:
    void build_player() override {
        player->set_player( true );

        player->set_damage(4);
        player->set_health(10);

        std::string name = "Knight";
        player->set_name(name);

        player->set_coefficient_damage(2);
        player->set_coefficient_health(2);
    }
    Knight_Player_Builder() = default;
};
class Archer_Player_Builder : public Player_Builder {
public:
    void build_player() override {
        player->set_player( true );

        player->set_damage(10);
        player->set_health(6);

        std::string name = "Archer";
        player->set_name(name);

        player->set_coefficient_damage(2);
        player->set_coefficient_health(2);
    }
    Archer_Player_Builder() = default;
};

class Shield_Player_Builder : public Player_Builder {
public:
    void build_player() override {
        player->set_player( true );

        player->set_damage(1);
        player->set_health(23);

        std::string name = "Shield";
        player->set_name(name);

        player->set_coefficient_damage(2);
        player->set_coefficient_health(2);
    }
    Shield_Player_Builder() = default;
};


class Player_Builder_Director {
private:
    std::shared_ptr<Player_Builder> player_builder;

public:
    Player_Builder_Director() = default;

    void set_player_builder(std::shared_ptr<Player_Builder> player_builder) {
        this->player_builder = player_builder;
    }

    void build_player() {
        player_builder->build_player();
    }

    std::shared_ptr<Player> get_player() {
        return player_builder->get_player();
    }
};