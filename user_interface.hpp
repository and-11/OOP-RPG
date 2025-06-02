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
    const int window_lengt = 800;
    const int window_height = 600;
    int player_selected = 0;
    int enemy_selected = 0;
    int item_selected;
    STATES state;

    sf::RenderWindow window;
    sf::Font font;

    void display_entity(Game *current_level);
    void display_items(Game *current_level);
public:
    UI();
    void Add_level(const Game &x);
    void start();
};
