#include "user_interface.hpp"

#include <map>

bool displayButton(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, sf::Font &font)
{
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    // Use original button area for hover detection
    sf::FloatRect baseBounds(position, size);
    if (baseBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
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

    // Compute scaled size and position if hovered
    sf::Vector2f drawSize = size;
    sf::Vector2f drawPosition = position;
    float textScale = 1.0f;

    if (isHovered)
    {
        drawSize *= 1.3f;
        drawPosition = position - (drawSize - size) / 2.0f;
        textScale = 1.3f;
    }

    // Transparent button (use outline if you want visual feedback)
    sf::RectangleShape button(drawSize);
    button.setPosition(drawPosition);
    button.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent

    // Create and center text
    sf::Text buttonText(text, font, 32);
    buttonText.setScale(textScale, textScale);
    buttonText.setFillColor(sf::Color::White);

    // Re-center text origin after scaling
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(drawPosition.x + drawSize.x / 2.0f, drawPosition.y + drawSize.y / 2.0f);

    window.draw(button);
    window.draw(buttonText);

    return isClicked;
}


bool displayAnimatedButton(
    sf::RenderWindow &window,
    const sf::Vector2f &position,
    const sf::Vector2f &size,
    const std::vector<sf::Texture> &frames,
    float frameDuration,
    sf::Clock &animationClock,
    bool h_flip = false,
    float spriteScaleFactor = 5.f)
{
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string((int)position.x) + "_" + std::to_string((int)position.y);
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

    // Base values
    sf::Vector2f drawSize = size;
    sf::Vector2f drawPosition = position;

    // Use hover detection on original size
    sf::FloatRect baseBounds(position, size);
    if (baseBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
        isHovered = true;
        drawSize = size * 1.1f;
        drawPosition = position - (drawSize - size) / 2.f;

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

    // Animate the sprite
    int frameIndex = static_cast<int>((animationClock.getElapsedTime().asSeconds() / frameDuration)) % frames.size();
    sf::Sprite sprite(frames[frameIndex]);

    sf::Vector2u texSize = sprite.getTexture()->getSize();

    float scaleX = (drawSize.x / texSize.x) * spriteScaleFactor;
    float scaleY = (drawSize.y / texSize.y) * spriteScaleFactor;

    sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);

    if (h_flip)
        scaleX = -scaleX;

    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(drawPosition.x + drawSize.x / 2.f, drawPosition.y + drawSize.y / 2.f);

    window.draw(sprite);

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

    int position_up = 0;
    int position_down = window_height - 300;

    // std::cout << current_level <<"\n";

    sf::Vector2f sf_entity_box_size(entity_box_size ,entity_box_size );

    for (int i = 0; i < ct_players; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_players - 1),1 ) * i;


        if (displayAnimatedButton(window, sf::Vector2f( horizontal_offset + i*30 ,position  ), sf_entity_box_size, 
            current_level->get_xth_player(i+1)->get_frames() , 0.1f, animation_clock, false,
            1.3
        ) )
        {
            player_selected = i;
            // std::cout << "PLAYER " + std::to_string( i ) + " clicked!\n";            
        }
    }

    for (int i = 0; i < ct_enemies; i++)
    {
        int position = position_up + (position_down - position_up) / std::max( (ct_enemies - 1),1 ) * i;
        if (displayAnimatedButton(window, sf::Vector2f( window_lengt-horizontal_offset -200 - i*30 , position ), sf_entity_box_size,
            current_level->get_xth_enemy(i+1)->get_frames() , 0.1f, animation_clock , true,
            1.4
        ) ) 
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
        window.draw(backgroundSprite); // draw background

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
            displayButton(window, sf::Vector2f( window_lengt/2-400 , window_height - vertical_offset ), sf::Vector2f(600.f, 60.f),
            "Chose a target for " + std::to_string( player_to_attack+1 ) + " to attack" , font) ;

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