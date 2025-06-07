//
// Created by jeff on 5/30/25.
//
#include "game.hpp"
#include "visitor.hpp"
#include "entity.hpp"
#include "enemy.hpp"
#include "player.hpp"

bool visitor_alive::visit_is_alive( Entity * x ) {
    return x->get_current_health() > 0;
}

bool visitor_is_over::visit_is_game_over( Game * x ) {
    return x->is_over();
}

