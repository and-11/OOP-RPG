#include "user_interface.hpp"

#include <map>

bool displayButton(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, sf::Font &font)
{
    static std::map<std::string, bool> holdMap;

    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    sf::RectangleShape button(size);
    button.setPosition(position);

    if (button.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
    {
        isHovered = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!isHeld)
            {
                isClicked = true;
                isHeld = true;
            }
        }
        else
        {
            isHeld = false;
        }
    }
    else
    {
        isHeld = false;
    }

    button.setFillColor(isClicked ? sf::Color::Green : (isHovered ? sf::Color::Red : sf::Color::Blue));

    // Create text with doubled character size
    sf::Text buttonText(text, font, 32); // Was 16
    buttonText.setFillColor(sf::Color::White);

    // Center the text
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);

    window.draw(button);
    window.draw(buttonText);

    return isClicked;
}





void UI::Add_level(const Game &x)
{
    levels.push_back(x);
}

void UI::display_items(Game *current_level)
{
    int ct_items = current_level->count_items();

    int position_up = 100;
    int position_down = window_height - 300;

    // std::cout << current_level <<"\n";

    

    for (int i = 0; i < ct_items; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_items - 1),1 ) * i;
        if (displayButton(window, sf::Vector2f( horizontal_offset ,position  ), sf::Vector2f(200.f, 60.f), "POTION "+std::to_string(i), font))
        {
            item_selected = i;
            std::cout << "item " + std::to_string( i+1 ) + "\n";            
        }
    }
}

void UI::display_entity(Game *current_level)
{
    int ct_players = current_level->count_players();
    int ct_enemies = current_level->count_enemies();

    int position_up = 100;
    int position_down = window_height - 300;

    // std::cout << current_level <<"\n";

    for (int i = 0; i < ct_players; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_players - 1),1 ) * i;
        if (displayButton(window, sf::Vector2f( horizontal_offset ,position  ), sf::Vector2f(200.f, 60.f), "HERO "+std::to_string(i), font))
        {
            player_selected = i;
            // std::cout << "PLAYER " + std::to_string( i ) + " clicked!\n";            
        }
    }

    for (int i = 0; i < ct_enemies; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_enemies - 1),1 ) * i;
        if (displayButton(window, sf::Vector2f( window_lengt-horizontal_offset -200 , position ), sf::Vector2f(200.f, 60.f), "ENEMY "+std::to_string(i), font))
        {
            enemy_selected = i;
            // std::cout << "  ENEMYE " + std::to_string( i ) + " clicked!\n";            
        }
    }

}

void UI::start()
{

    clear_window();

    // sf::RenderWindow window(sf::VideoMode(window_lengt, window_height), "OOP RPG");

    // window(sf::VideoMode(window_lengt, window_height), "OOP RPG");


    sf::Texture backgroundTexture; /// BACKGROUND
    if (!backgroundTexture.loadFromFile("background.png"))
    {
        std::cerr << "Failed to load background.png\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    // Scale
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y);

    sf::Clock animationClock;

    //////////////////////////////////////////////////////////////////////////////          ACTUALY START

    int index_level = 0;
    
    Game *current_level = &levels[ 0 ];
    current_level->prepare_fight();
    item_selected = -1;

    int player_to_attack ;

    
    current_level->show_status();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or current_level->count_players()==0 or index_level == int(levels.size()) )
                window.close();
        }

        window.clear();                // still keep this
        // window.draw(backgroundSprite); // draw background

        player_selected = enemy_selected = -1;

        if( state != USE_ITEM )
            display_entity(current_level);
        
        // std::cout << current_level->count_enemies() <<"\n";  
        if( !current_level->count_enemies() )   /// next level
        {
            clear_window();
            current_level->load();
            if ( index_level < int(levels.size()) - 1)
            {
                current_level->game_transfer(levels[index_level + 1]);
                current_level = &levels[ index_level+1 ];
                current_level->prepare_fight();
                current_level->show_status();

            }
            index_level++;
            state = CHOSE_ACTION;
        }
        if( state == USE_ITEM )
        {
            display_items(current_level);
            
            if( item_selected != -1 )
                state = TARGET_SELECTION_ITEM;
            
            if (displayButton(window, sf::Vector2f( horizontal_offset + (window_lengt-2*horizontal_offset)/3 +square_button_size , window_height -vertical_offset ), sf::Vector2f(square_button_size, square_button_size), "Item", font))
            {
                state = CHOSE_ACTION;
            }
        }

        if( state == CHOSE_ACTION )
        {

            if (displayButton(window, sf::Vector2f( horizontal_offset, window_height -vertical_offset ), sf::Vector2f(square_button_size, square_button_size), "Attack", font))
            {
                state = ATTACK ;
                player_to_attack = 0;
                enemy_selected = -1;

                std::cout << "Attack \n" ;           
            }

            if (displayButton(window, sf::Vector2f( horizontal_offset + (window_lengt-2*horizontal_offset)/3 +square_button_size , window_height -vertical_offset ), sf::Vector2f(square_button_size, square_button_size), "Item", font))
            {
                state = USE_ITEM;

                std::cout << "Select item "  << " \n" ;     
                current_level->show_items();
            }

            if (displayButton(window, sf::Vector2f( window_lengt - horizontal_offset - square_button_size , window_height -vertical_offset ), sf::Vector2f(square_button_size, square_button_size), "Info", font))
            {
                state = SEE_DETAILS;

                std::cout << "See details "  << " \n" ;     
            }
            
        }   
        if( state == SEE_DETAILS )
        {
            if( enemy_selected != -1 )
            {
                current_level->show_enemy_details( enemy_selected+1 );
                state = CHOSE_ACTION;
            }
        }

        if( state == TARGET_SELECTION_ITEM )
        {
            if( player_selected != -1 )
            {
                std::cout  <<  item_selected+1 << " " << player_selected+1 << "\n";
                current_level->count_item_use_player( item_selected+1,player_selected+1 );
                state = CHOSE_ACTION;
                item_selected = -1;
                current_level->enemy_turn();
                current_level->show_status();
                
            }
            if( enemy_selected != -1 )
            {
                current_level->count_item_use_enemy( item_selected+1,enemy_selected+1 );
                state = CHOSE_ACTION;
                item_selected = -1;      
                current_level->enemy_turn();
                current_level->show_status();
            }
        }
        if( state == ATTACK )
        {
            displayButton(window, sf::Vector2f( horizontal_offset , window_height - vertical_offset ), sf::Vector2f(300.f, 60.f),
            "chose a target for " + std::to_string( player_to_attack+1 ) + " to attack" , font) ;

            if( player_to_attack == current_level->count_players() or !current_level->count_enemies() )
                state = CHOSE_ACTION ;

            if( player_to_attack == current_level->count_players() )
            {
                current_level->enemy_turn();
                current_level->show_status();
            }


            if( enemy_selected != -1 )
            {
                current_level->count_attack( player_to_attack+1, enemy_selected+1 );
                
                enemy_selected = -1;
                player_to_attack ++ ;
            }
        }
        

                            
                

        

        window.display();
    }
}

UI::UI() : window(sf::VideoMode(window_lengt, window_height), "OOP RPG")
{
    if (!font.loadFromFile("SF Pixelate Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }
    state = CHOSE_ACTION;
}