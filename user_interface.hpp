#pragma once

#include "game.hpp"
#include "functions.hpp"
#include "exception.hpp"

class UI {
private:
    std::vector<Game> levels;

    void attack(Game* current_level);
    void see_detail(Game* current_level);
    bool chose_item(Game* current_level);
    void chose_action(Game* current_level);
    static void option_at_it_info();

public:
    void Add_level(const Game& x);
    void start();
};
