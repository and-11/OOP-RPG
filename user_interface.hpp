#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "functions.hpp"
#include "exception.hpp"
#include "visitor.hpp"

enum STATES { CHOSE_ACTION, USE_ITEM, ATTACK, TARGET_SELECTION };

class UI {
private:
    std::vector<Game> levels;
    const int window_lengt = 800;
    const int window_height = 600;
    int player_selected =0;
    int enemy_selected =0;
    STATES state;

    sf::RenderWindow window; 
    sf::Font font;

    void attack(Game* current_level);
    void see_detail(Game* current_level);
    bool chose_item(Game* current_level);
    void chose_action(Game* current_level);
    static void option_at_it_info();
    void display_entity(Game* current_level);
    public:
    UI();
    void Add_level(const Game& x);
    void start();
};
