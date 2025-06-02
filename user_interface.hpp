#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "functions.hpp"
#include "exception.hpp"
#include "visitor.hpp"

class UI {
private:
    std::vector<Game> levels;
    const int window_lengt = 1600;
    const int window_height = 1200;
 
    sf::RenderWindow window; 
    sf::Font font;

    void attack(Game* current_level);
    void see_detail(Game* current_level);
    bool chose_item(Game* current_level);
    void chose_action(Game* current_level);
    static void option_at_it_info();
    void display_level(Game* current_level);
    public:
    UI();
    void Add_level(const Game& x);
    void start();
};
