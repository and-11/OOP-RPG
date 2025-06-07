#pragma once

#include "libraries.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "exception.hpp"
#include "enemy.hpp"
#include "visitor.hpp"

class Game {
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Item>> items;
    bool game_is_lost;
    visitor_alive vis;
public:
    Game();
    ~Game();

    [[nodiscard]] bool accept_visit( visitor_is_over vis );

    [[nodiscard]] bool is_game_lost() const;
    [[nodiscard]] int count_players() const;
    [[nodiscard]] int count_enemies() const;
    [[nodiscard]] int count_items() const;

    void add_creature(const std::shared_ptr<Entity>& dude);
    void add_item(const std::shared_ptr<Item>& it);
    void game_transfer(Game& next_level) const;

    void show_players() const;
    void show_enemies() const;
    void show_status() const;
    void show_items();

    void prepare_fight();
    // void attack(const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b);
    
    std::shared_ptr<Item> get_xth_item(int ct);
    std::shared_ptr<Entity> get_xth_enemy(int ct);
    std::shared_ptr<Entity> get_xth_player(int ct);

    void count_attack(int ct_player, int ct_enemy);
    void enemy_turn();
    bool is_over();

    std::string th_player_name(int i);
    void show_enemy_details(int ct);

    void count_item_use_enemy(int i, int ct_enemy);
    void count_item_use_player(int i, int ct_player);

    void reset();
    static void load();

    template<typename A,typename B>
    void attack(const std::shared_ptr<A>& a, const std::shared_ptr<B>& b) {
        b->recive_damage(a->get_damage());
        std::cout << a->get_name() << " attacked " << b->get_name()
                  << " for " << a->show_damage() << "\n";
    }
};
