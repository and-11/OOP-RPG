#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "functions.hpp"
#include "exception.hpp"
#include "visitor.hpp"

enum STATES
{
    CHOSE_ACTION,
    USE_ITEM,
    ATTACK,
    TARGET_SELECTION_ITEM,
    SEE_DETAILS
};



class UI
{
private:
    std::vector<Game> levels;

    const int window_lengt = 1000;
    const int window_height = 750;
    int player_selected = 0;
    int enemy_selected = 0;
    int item_selected;
    STATES state;

    sf::RenderWindow window;
    sf::Font font;
    sf::Clock animation_clock;

    const int horizontal_offset = 100;
    const int vertical_offset = 150;
    const int entity_box_size = 120;

    const int square_button_size = 120;
    
    void display_entity(Game *current_level);
    void display_items(Game *current_level);
public:
    UI();
    void Add_level(const Game &x);
    void start();
};