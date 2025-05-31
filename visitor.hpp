#pragma once

class Entity;
class Game;

class visitor {
    public:
    virtual ~visitor() = default;
};

class visitor_alive : public visitor {
public:
    bool visit_is_alive( Entity * x );
};
//
class visitor_is_over : public visitor {
public:
    bool visit_is_game_over( Game * x );
};
