#include "user_interface.hpp"
#include <map>

bool displayButton(sf::RenderWindow &window, const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, sf::Font &font)
{
    static std::map<std::string, bool> holdMap;
    std::string key = std::to_string(static_cast<int>(position.x)) + "_" + std::to_string(static_cast<int>(position.y));
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isHovered = false, isClicked = false;

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

    sf::Vector2f drawSize = size;
    sf::Vector2f drawPosition = position;
    float textScale = 1.0f;

    if (isHovered)
    {
        drawSize *= 1.3f;
        drawPosition = position - (drawSize - size) / 2.0f;
        textScale = 1.3f;
    }

    sf::RectangleShape button(drawSize);
    button.setPosition(drawPosition);
    button.setFillColor(sf::Color(0, 0, 0, 0));

    sf::Text buttonText(text, font, 32);
    buttonText.setScale(textScale, textScale);
    buttonText.setFillColor(sf::Color::White);

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
    std::string key = std::to_string(static_cast<int>(position.x)) + "_" + std::to_string(static_cast<int>(position.y));
    bool &isHeld = holdMap[key];

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isClicked = false;

    sf::Vector2f drawSize = size;
    sf::Vector2f drawPosition = position;

    sf::FloatRect baseBounds(position, size);
    if (baseBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
    {
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

    int frameIndex = static_cast<int>((animationClock.getElapsedTime().asSeconds() / frameDuration)) % static_cast<int>(frames.size());
    sf::Sprite sprite(frames[frameIndex]);

    sf::Vector2u texSize = sprite.getTexture()->getSize();

    float scaleX = (drawSize.x / static_cast<float>(texSize.x)) * spriteScaleFactor;
    float scaleY = (drawSize.y / static_cast<float>(texSize.y)) * spriteScaleFactor;

    sprite.setOrigin(static_cast<float>(texSize.x) / 2.f, static_cast<float>(texSize.y) / 2.f);

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

    for (int i = 0; i < ct_items; i++)
    {
        int position = position_up + (position_down - position_up) / std::max(ct_items - 1, 1) * i;
        if (displayButton(window, sf::Vector2f(horizontal_offset + (window_lengt - 2 * horizontal_offset) / 3.f + square_button_size, static_cast<float>(position)),
                          sf::Vector2f(200.f, 60.f),
                          current_level->get_xth_item(i + 1)->get_name(), font))
        {
            item_selected = i;
            std::cout << "item " + std::to_string(i + 1) + "\n";
        }
    }
}

void UI::display_entity(Game *current_level)
{
    int ct_players = current_level->count_players();
    int ct_enemies = current_level->count_enemies();

    int position_up = 0;
    int position_down = window_height - 300;

    sf::Vector2f sf_entity_box_size(entity_box_size, entity_box_size);

    for (int i = 0; i < ct_players; i++)
    {
        int position = position_up + (position_down - position_up) / std::max(ct_players - 1, 1) * i;

        if (displayAnimatedButton(window, sf::Vector2f(horizontal_offset, static_cast<float>(position)), sf_entity_box_size,
                                  current_level->get_xth_player(i + 1)->get_frames(), 0.1f, animation_clock, false,
                                  1.3f))
        {
            player_selected = i;
        }
    }

    for (int i = 0; i < ct_enemies; i++)
    {
        int position = position_up + (position_down - position_up) / std::max(ct_enemies - 1, 1) * i;
        if (displayAnimatedButton(window, sf::Vector2f(window_lengt - horizontal_offset - 150, static_cast<float>(position)), sf_entity_box_size,
                                  current_level->get_xth_enemy(i + 1)->get_frames(), 0.1f, animation_clock, true,
                                  1.4f))
        {
            enemy_selected = i;
        }
    }
}

void UI::start()
{
    clear_window();

    sf::Texture backgroundTexture,backgroundTexture1,backgroundTexture2;
    if (!backgroundTexture.loadFromFile("background.png"))
    {
        std::cerr << "Failed to load background.png\n";
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    if (!backgroundTexture1.loadFromFile("background1.png"))
    {
        std::cerr << "Failed to load background1.png\n";
        return;
    }
    sf::Sprite backgroundSprite1(backgroundTexture1);

    if (!backgroundTexture2.loadFromFile("background2.png"))
    {
        std::cerr << "Failed to load background2.png\n";
        return;
    }
    sf::Sprite backgroundSprite2(backgroundTexture2);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y);

    int index_level = 0;

    Game *current_level = &levels[0];
    current_level->prepare_fight();
    item_selected = -1;

    int player_to_attack = 0;

    current_level->show_status();

    bool won = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (current_level->count_players() == 0)
        {
            window.close();
        }
        if (index_level == static_cast<int>(levels.size()))
        {
            won = true;
            window.close();
        }

        window.clear();

        if( index_level == 4 )
            window.draw(backgroundSprite2);
        else if( index_level < 2 )
            window.draw(backgroundSprite);
        else 
            window.draw(backgroundSprite1);




        player_selected = enemy_selected = -1;

        if (state != USE_ITEM)
            display_entity(current_level);

        displayButton(window, sf::Vector2f(horizontal_offset + (window_lengt - 2 * horizontal_offset) / 3.f + square_button_size, 20.f), sf::Vector2f(square_button_size, square_button_size),
                      "Stage " + std::to_string(index_level + 1), font);

        if (!current_level->count_enemies())
        {
            clear_window();
            current_level->load();
            if (index_level < static_cast<int>(levels.size()) - 1)
            {
                current_level->game_transfer(levels[index_level + 1]);
                current_level = &levels[index_level + 1];
                current_level->prepare_fight();
                current_level->show_status();
            }
            index_level++;
            state = CHOSE_ACTION;
        }

        if (state == USE_ITEM)
        {
            display_items(current_level);

            if (item_selected != -1)
                state = TARGET_SELECTION_ITEM;

            if (displayButton(window, sf::Vector2f(horizontal_offset + (window_lengt - 2 * horizontal_offset) / 3.f + square_button_size, static_cast<float>(window_height - vertical_offset)), sf::Vector2f(square_button_size, square_button_size), "Item", font))
            {
                state = CHOSE_ACTION;
            }
        }

        if (state == CHOSE_ACTION)
        {
            if (displayButton(window, sf::Vector2f(horizontal_offset, static_cast<float>(window_height - vertical_offset)), sf::Vector2f(square_button_size, square_button_size), "Attack", font))
            {
                state = ATTACK;
                player_to_attack = 0;
                enemy_selected = -1;
            }

            if (displayButton(window, sf::Vector2f(horizontal_offset + (window_lengt - 2 * horizontal_offset) / 3.f + square_button_size, static_cast<float>(window_height - vertical_offset)), sf::Vector2f(square_button_size, square_button_size), "Item", font))
            {
                state = USE_ITEM;
                current_level->show_items();
            }

            if (displayButton(window, sf::Vector2f(window_lengt - horizontal_offset - square_button_size, static_cast<float>(window_height - vertical_offset)), sf::Vector2f(square_button_size, square_button_size), "Info", font))
            {
                state = SEE_DETAILS;
            }
        }

        if (state == SEE_DETAILS)
        {
            if (enemy_selected != -1)
            {
                current_level->show_enemy_details(enemy_selected + 1);
                state = CHOSE_ACTION;
            }
        }

        if (state == TARGET_SELECTION_ITEM)
        {
            if (player_selected != -1)
            {
                current_level->count_item_use_player(item_selected + 1, player_selected + 1);
                state = CHOSE_ACTION;
                item_selected = -1;
                current_level->enemy_turn();
                current_level->show_status();
            }
            if (enemy_selected != -1)
            {
                current_level->count_item_use_enemy(item_selected + 1, enemy_selected + 1);
                state = CHOSE_ACTION;
                item_selected = -1;
                current_level->enemy_turn();
                current_level->show_status();
            }
        }

        if (state == ATTACK)
        {
            displayButton(window, sf::Vector2f(window_lengt / 2.f - 400.f, static_cast<float>(window_height - vertical_offset)), sf::Vector2f(600.f, 60.f),
                          "Chose a target for " + std::to_string(player_to_attack + 1) + " to attack", font);

            if (!current_level->count_enemies())
            {
                state = CHOSE_ACTION;
                player_to_attack = 0;
                continue;
            }

            if (player_to_attack >= current_level->count_players())
            {
                current_level->enemy_turn();
                current_level->show_status();
                state = CHOSE_ACTION;
                player_to_attack = 0;
            }
            else if (enemy_selected != -1)
            {
                // std::cout << player_to_attack + 1  <<  ":  "<< enemy_selected + 1 << "\n";
                current_level->count_attack(player_to_attack + 1, enemy_selected + 1);
                enemy_selected = -1;
                player_to_attack++;
            }
        }

        window.display();
    }
    if (won)
        std::cout << "\nYOU WON\n";
    else
        std::cout << "\nYOU LOST\n";
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
