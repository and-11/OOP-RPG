#pragma once

// #include "entity.hpp"

// #include "game.hpp"

class Entity;

class visitor {
    public:
    virtual ~visitor() = default;
};

class visitor_alive : public visitor {
public:
    bool visit_is_alive( Entity * x );
};
//
// class visitor_is_over : public visitor {
// public:
//     bool visit_is_game_over( const std::shared_ptr<Game>& x ) const {
//         return x->is_over();
//     }
// };
