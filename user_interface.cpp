#include "user_interface.hpp"

void UI::Add_level(const Game& x) {
    levels.push_back(x);
}

void UI::attack(Game* current_level) {
    current_level->show_players();
    std::cout << "\n";
    for (int i = 1; i <= current_level->count_players(); i++) {
        if (!current_level->count_enemies()) break;

        std::cout << "\nChoose an enemy for " << current_level->th_player_name(i) << " to attack:\n";
        current_level->show_enemies();

        while (true) {
            try {
                int option = get_numeric_input();
                current_level->count_attack(i, option);
                break;
            } catch (MyException& e) {
                std::cout << e.what() << "\n";
            }
        }
    }
    std::cout << "\n";
}

void UI::see_detail(Game* current_level) {
    std::cout << "Choose an enemy to view details about:\n";
    current_level->show_enemies();

    while (true) {
        try {
            int option = get_numeric_input();
            current_level->show_enemy_details(option);
            break;
        } catch (MyException& e) {
            std::cout << e.what() << "\n";
        }
    }
}

bool UI::chose_item(Game* current_level) {
    current_level->show_items();
    std::cout << "\nChoose an item or press 0 to cancel:\n";

    std::shared_ptr<Item> current_item;

    while (true) {
        try {
            int option = get_numeric_input();
            if (option == 0) {
                clear_window();
                option_at_it_info();
                return false;
            } else {
                current_item = current_level->get_xth_item(option);
                break;
            }
        } catch (MyException& e) {
            std::cout << e.what() << "\n";
        }
    }

    std::cout << current_item->get_name() << ": Press 1 to use on a PLAYER and 2 to use on an ENEMY:\n";

    while (true) {
        try {
            int option = get_numeric_input();
            if (option == 1) {
                std::cout << "\nChoose a Hero to use " << current_item->get_name() << " on:\n";
                current_level->show_players();
                while (true) {
                    try {
                        int h_option = get_numeric_input();
                        current_level->count_item_use_player(current_item, h_option);
                        break;
                    } catch (MyException& e) {
                        std::cout << e.what() << "\n";
                    }
                }
                break;
            } else if (option == 2) {
                std::cout << "\nChoose an enemy to use " << current_item->get_name() << " on:\n";
                current_level->show_enemies();
                while (true) {
                    try {
                        int e_option = get_numeric_input();
                        current_level->count_item_use_enemy(current_item, e_option);
                        break;
                    } catch (MyException& e) {
                        std::cout << e.what() << "\n";
                    }
                }
                break;
            }
            throw Input_Invalid();
        } catch (MyException& e) {
            std::cout << e.what() << "\n";
        }
    }
    return true;
}

void UI::option_at_it_info() {
    std::cout << "\nPress 1 to attack, 2 to use an item, or 3 to see enemy details:\n";
}

void UI::chose_action(Game* current_level) {
    option_at_it_info();
    while (true) {
        try {
            int option = get_numeric_input();
            if (option >= 1 && option <= 3) clear_window();

            if (option == 1) {
                attack(current_level);
                break;
            } else if (option == 2) {
                if (chose_item(current_level))
                    break;
                else
                    continue;
            } else if (option == 3) {
                see_detail(current_level);
                option_at_it_info();
                continue;
            }
            throw Input_Invalid();
        } catch (MyException& e) {
            std::cout << e.what() << "\n";
        }
    }
}

void UI::start() {
    clear_window();

    bool lose = false;
    visitor_is_over vis;

    for (size_t i = 0; i < levels.size(); i++) {
        std::cout << "LEVEL " << i << ":\n";
        Game* current_level = &levels[i];
        current_level->prepare_fight();

        while ( !current_level->accept_visit(vis) ) {
            current_level->show_status();
            chose_action(current_level);
            current_level->enemy_turn();
        }

        if (current_level->is_game_lost()) {
            lose = true;
            break;
        } else if (i < levels.size() - 1) {
            Game::load();
            clear_window();
            current_level->game_transfer(levels[i + 1]);
        }
        std::cout << "\033[32mYou passed level " << i << "\n\033[0m\n";
    }

    if (!lose) {
        std::cout << "\033[32m\nCONGRATULATIONS\nYOU WON THE GAME!!!\033[0m\n\n\n";
    }
}
