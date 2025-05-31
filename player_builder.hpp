#pragma once

#include "functions.hpp"
#include "player.hpp"

class Player_Builder
{
protected:
    std::shared_ptr<Player> player;
public:
    Player_Builder();

    virtual void build_player() = 0;

    [[nodiscard]] std::shared_ptr<Player> get_player() const;

    virtual ~Player_Builder() = default;
};

class Knight_Player_Builder : public Player_Builder {
public:
    void build_player() override;
    Knight_Player_Builder() = default;
};
class Archer_Player_Builder : public Player_Builder {
public:
    void build_player() override ;

    Archer_Player_Builder() = default;
};

class Shield_Player_Builder : public Player_Builder {
public:
    void build_player() override ;
    Shield_Player_Builder() = default;
};


class Player_Builder_Director {
private:
    std::shared_ptr<Player_Builder> player_builder;

public:
    Player_Builder_Director() = default;

    void set_player_builder(std::shared_ptr<Player_Builder> player_builder);

    void build_player();

    std::shared_ptr<Player> get_player();
};