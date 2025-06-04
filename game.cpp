#include "game.hpp"
#include "functions.hpp"
#include "random.hpp"

Game::Game() : game_is_lost{false} {}

Game::~Game() {
    entities.clear();
    items.clear();
}

[[nodiscard]] bool Game::is_game_lost() const {
    return game_is_lost;
}

[[nodiscard]] bool Game::accept_visit( visitor_is_over vis ) {
    return vis.visit_is_game_over(this);
}

void Game::add_creature(const std::shared_ptr<Entity>& dude) {
    entities.push_back(dude);
}

void Game::add_item(const std::shared_ptr<Item>& it) {
    items.push_back(it);
}

void Game::game_transfer(Game& next_level) const {
    for (const auto& x : entities)
        if (x->is_player())
            next_level.add_creature(x);
    for (const auto& x : items)
        next_level.add_item(x);
}

int Game::count_players() const {
    int ct = 0;
    for (const auto& x : entities)
        if (x->accept_visit(vis) && x->is_player())
            ct++;
    return ct;
}

int Game::count_enemies() const {
    int ct = 0;
    for (const auto& x : entities)
        if (x->accept_visit(vis) && !x->is_player())
            ct++;
    return ct;
}

int Game::count_items() const {
    return int(items.size());
}

void Game::show_players() const {
    int ct = 0;
    std::cout << "\033[32m";
    if (count_players() > 0)
        std::cout << "Heroes\n";
    std::cout << "\033[0m";
    for (const auto& x : entities)
        if (x->accept_visit(vis) && x->is_player())
            std::cout << "#" << (++ct) << " " << (*x) << "\n";
}

void Game::show_enemies() const {
    int ct = 0;
    std::cout << "\033[31m";
    if (count_enemies() > 0)
        std::cout << "Enemies\n";
    std::cout << "\033[0m";
    for (const auto& x : entities)
        if (x->accept_visit(vis) && !x->is_player())
            std::cout << "#" << (++ct) << " " << (*x) << "\n";
}

void Game::show_status() const {
    std::cout << "\n";
    show_players();
    show_enemies();
    std::cout << "\n";
}

void Game::show_items() {
    int ct = 0;
    for (const auto& x : items)
        std::cout << "\033[36m#" << ++ct << " " << (*x) << "\n";
}

void Game::prepare_fight() {
    for (const auto& x : entities)
        x->Ready();
}



std::shared_ptr<Item> Game::get_xth_item(int ct) {
    if (ct < 1) throw Input_too_low();
    if (ct > count_items()) throw Input_too_high();
    return items[ct - 1];
}

std::shared_ptr<Entity> Game::get_xth_enemy(int ct) {
    int og_ct = ct;
    for (const auto& x : entities)
        if (x->accept_visit(vis) && !x->is_player()) {
            ct--;
            if (!ct) return x;
        }
    if (og_ct < 1) throw Input_too_low();
    if (og_ct > count_enemies()) throw Input_too_high();
    return {};
}

std::shared_ptr<Entity> Game::get_xth_player(int ct) {
    int og_ct = ct;
    for (const auto& x : entities)
        if (x->accept_visit(vis) && x->is_player()) {
            ct--;
            if (!ct) return x;
        }
    if (og_ct < 1) throw Input_too_low();
    if (og_ct > count_players()) throw Input_too_high();
    return {};
}

void Game::count_attack(int ct_player, int ct_enemy) {
    // std::cerr << "s-a ajuns";
    auto pl = get_xth_player(ct_player);
    auto en = get_xth_enemy(ct_enemy);
    attack(pl, en);
}

void Game::enemy_turn() {
    for (const auto& x : entities)
        if (x->accept_visit(vis) && !x->is_player()) {
            if (count_players() == 0) break;

            random_cls<int>r;
            int who = r.get_random_number() % count_players() + 1;
            int ct = 0;
            for (const auto& y : entities)
                if (y->accept_visit(vis) && y->is_player()) {
                    ct++;
                    if (ct == who) {
                        attack(x, y);
                        break;
                    }
                }
        }
}

bool Game::is_over() {
    if (!count_enemies()) {
        std::cout << "\033[1;35mYOU WON THIS LEVEL!\n\033[0m";
        return true;
    } else if (!count_players()) {
        game_is_lost = true;
        std::cout << "\033[33mYOU LOST!\n\033[0m";
        return true;
    }
    return false;
}

std::string Game::th_player_name(int i) {
    try {
        int ct = 0;
        for (const auto& x : entities)
            if (x->accept_visit(vis) && x->is_player()) {
                ct++;
                if (ct == i) return x->get_name();
            }
        throw Input_Invalid();
    } catch (MyException& e) {
        return e.what();
    }
}

void Game::show_enemy_details(int ct) {
    auto ent = get_xth_enemy(ct);
    auto ene = std::dynamic_pointer_cast<Enemy>(ent);
    ene->show_informations();
}

void Game::count_item_use_enemy(int item, int ct_enemy) {
    get_xth_item(item)->use(*get_xth_enemy(ct_enemy));
    std::cout << "\n";
}

void Game::count_item_use_player(int item, int ct_player) {
    get_xth_item(item)->use(*get_xth_player(ct_player));
    std::cout << "\n";
}

void Game::reset() {
    entities.clear();
    items.clear();   
    game_is_lost = false;
}

void Game::load() {
    std::cout << "\nLoading next level...\n\n";
}
