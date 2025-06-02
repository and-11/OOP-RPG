#include "user_interface.hpp"

#include <map>

// Custom-size text button
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

    sf::Text buttonText(text, font, 16);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(position.x + 5, position.y + 5);

    window.draw(button);
    window.draw(buttonText);

    return isClicked;
}

// Custom-size image button
bool displayImageButton(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size, sf::Sprite &sprite)
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
    window.draw(button);

    sprite.setPosition(position);
    sprite.setScale(
        size.x / sprite.getTexture()->getSize().x,
        size.y / sprite.getTexture()->getSize().y);
    window.draw(sprite);

    return isClicked;
}

bool displayAnimatedButton(
    sf::RenderWindow &window,
    const sf::Vector2f &position,
    const sf::Vector2f &size,
    const std::vector<sf::Texture> &frames,
    float frameDuration,
    sf::Clock &animationClock)
{
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    sf::RectangleShape button(size);
    button.setPosition(position);

    if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
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

    // No color background if sprite fully covers it — optional:
    // button.setFillColor(...);
    // window.draw(button);

    // Get current animation frame
    int frameIndex = static_cast<int>((animationClock.getElapsedTime().asSeconds() / frameDuration)) % frames.size();
    sf::Sprite sprite(frames[frameIndex]);

    // Scale sprite to exactly match button size
    sf::Vector2u texSize = sprite.getTexture()->getSize();
    float scaleX = size.x / texSize.x;
    float scaleY = size.y / texSize.y;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(position);

    window.draw(sprite);

    return isClicked;
}

void UI::Add_level(const Game &x)
{
    levels.push_back(x);
}

void UI::attack(Game *current_level)
{
    current_level->show_players();
    std::cout << "\n";
    for (int i = 1; i <= current_level->count_players(); i++)
    {
        if (!current_level->count_enemies())
            break;

        std::cout << "\nChoose an enemy for " << current_level->th_player_name(i) << " to attack:\n";
        current_level->show_enemies();

        while (true)
        {
            try
            {
                int option = get_numeric_input();
                current_level->count_attack(i, option);
                break;
            }
            catch (MyException &e)
            {
                std::cout << e.what() << "\n";
            }
        }
    }
    std::cout << "\n";
}

void UI::see_detail(Game *current_level)
{
    std::cout << "Choose an enemy to view details about:\n";
    current_level->show_enemies();

    while (true)
    {
        try
        {
            int option = get_numeric_input();
            current_level->show_enemy_details(option);
            break;
        }
        catch (MyException &e)
        {
            std::cout << e.what() << "\n";
        }
    }
}

bool UI::chose_item(Game *current_level)
{
    current_level->show_items();
    std::cout << "\nChoose an item or press 0 to cancel:\n";

    std::shared_ptr<Item> current_item;

    while (true)
    {
        try
        {
            int option = get_numeric_input();
            if (option == 0)
            {
                clear_window();
                option_at_it_info();
                return false;
            }
            else
            {
                current_item = current_level->get_xth_item(option);
                break;
            }
        }
        catch (MyException &e)
        {
            std::cout << e.what() << "\n";
        }
    }

    std::cout << current_item->get_name() << ": Press 1 to use on a PLAYER and 2 to use on an ENEMY:\n";

    while (true)
    {
        try
        {
            int option = get_numeric_input();
            if (option == 1)
            {
                std::cout << "\nChoose a Hero to use " << current_item->get_name() << " on:\n";
                current_level->show_players();
                while (true)
                {
                    try
                    {
                        int h_option = get_numeric_input();
                        current_level->count_item_use_player(current_item, h_option);
                        break;
                    }
                    catch (MyException &e)
                    {
                        std::cout << e.what() << "\n";
                    }
                }
                break;
            }
            else if (option == 2)
            {
                std::cout << "\nChoose an enemy to use " << current_item->get_name() << " on:\n";
                current_level->show_enemies();
                while (true)
                {
                    try
                    {
                        int e_option = get_numeric_input();
                        current_level->count_item_use_enemy(current_item, e_option);
                        break;
                    }
                    catch (MyException &e)
                    {
                        std::cout << e.what() << "\n";
                    }
                }
                break;
            }
            throw Input_Invalid();
        }
        catch (MyException &e)
        {
            std::cout << e.what() << "\n";
        }
    }
    return true;
}

void UI::option_at_it_info()
{
    std::cout << "\nPress 1 to attack, 2 to use an item, or 3 to see enemy details:\n";
}

void UI::chose_action(Game *current_level)
{
    option_at_it_info();
    while (true)
    {
        try
        {
            int option = get_numeric_input();
            if (option >= 1 && option <= 3)
                clear_window();

            if (option == 1)
            {
                attack(current_level);
                break;
            }
            else if (option == 2)
            {
                if (chose_item(current_level))
                    break;
                else
                    continue;
            }
            else if (option == 3)
            {
                see_detail(current_level);
                option_at_it_info();
                continue;
            }
            throw Input_Invalid();
        }
        catch (MyException &e)
        {
            std::cout << e.what() << "\n";
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

    const int offset = 100;

    for (int i = 0; i < ct_players; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_players - 1),1 ) * i;
        if (displayButton(window, sf::Vector2f( offset ,position  ), sf::Vector2f(200.f, 60.f), "HERO "+std::to_string(i), font))
        {
            player_selected = i;
            std::cout << "PLAYER " + std::to_string( i ) + " clicked!\n";            
        }
    }

    for (int i = 0; i < ct_enemies; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_enemies - 1),1 ) * i;
        if (displayButton(window, sf::Vector2f( window_lengt-offset -200 , position ), sf::Vector2f(200.f, 60.f), "ENEMY "+std::to_string(i), font))
        {
            enemy_selected = i;
            std::cout << "  ENEMYE " + std::to_string( i ) + " clicked!\n";            
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
    bool lose = false;
    visitor_is_over vis;

        /// eventual adauga visitor inapoi 

        // current_level->prepare_fight();  when next level
    
    Game *current_level = &levels[ 0 ];
    current_level->prepare_fight();

    bool potion_menu_visible = 0;
    bool all_menu_visible = 1;

    int player_to_attack ;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or current_level->count_players()==0 or index_level == levels.size() )
                window.close();
        }

        window.clear();                // still keep this
        // window.draw(backgroundSprite); // draw background


        display_entity(current_level);
        
        std::cout << current_level->count_enemies() <<"\n";  
        if( !current_level->count_enemies() )   /// next level
        {
            current_level->load();
            if ( index_level < levels.size() - 1)
            {
                current_level->game_transfer(levels[index_level + 1]);
                current_level = &levels[ index_level+1 ];
                current_level->prepare_fight();
            }
            index_level++;
        }


        if( state == CHOSE_ACTION )
        {

            if (displayButton(window, sf::Vector2f( 50, window_height -100 ), sf::Vector2f(200.f, 60.f), "Attack", font))
            {
                state = ATTACK ;
                player_to_attack = 0;
                enemy_selected = -1;

                std::cout << "Atacam frate \n" ;           
            }

            if (displayButton(window, sf::Vector2f( window_lengt/3+100, window_height -100 ), sf::Vector2f(200.f, 60.f), "Item", font))
            {
                potion_menu_visible = !potion_menu_visible; 
                std::cout << "ITEM clicked! " << potion_menu_visible << " \n" ;           
            }
            
            if( potion_menu_visible )
            {
                // display_potions()
            }
        }   
        if( state == ATTACK )
        {
            displayButton(window, sf::Vector2f( 50, window_height -100 ), sf::Vector2f(300.f, 60.f),
            "chose a target for " + std::to_string( player_to_attack+1 ) + "to attack" , font) ;

            if( player_to_attack == current_level->count_players() )
                current_level->enemy_turn();

            if( player_to_attack == current_level->count_players() or !current_level->count_enemies() )
                state = CHOSE_ACTION ;

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
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return;
    }
    state = CHOSE_ACTION;
}