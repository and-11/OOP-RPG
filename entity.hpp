#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "visitor.hpp"

#include <SFML/Graphics.hpp>

class Potion; 

class Entity {
protected:
    int level, damage, health, current_health, current_damage;
    int coefficient_damage, coefficient_health;
    std::string name;
    bool player;
    std::vector<sf::Texture> frames;

public:
    void set_level(int level);
    void set_damage(int damage);
    void set_health(int health);
    void set_name(const std::string& name);
    void set_player(bool player);
    void set_coefficient_damage(int coefficient_damage);
    void set_coefficient_health(int coefficient_health);

    void add_frames( int number_of_frames,std::string path );
    
    std::vector<sf::Texture> get_frames();

    Entity(); 
    Entity(const Entity& other);
    Entity& operator=(const Entity& other); 
    virtual ~Entity() = default;

    Entity(int level, int damage, int health, const std::string& name, int c_damage, int c_health);

    [[nodiscard]] bool is_alive() const;
    [[nodiscard]] bool is_player() const;
    [[nodiscard]] int get_damage() const;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::string show_damage() const;

    void Ready();
    void recive_damage(int value);

    friend std::ostream& operator<<(std::ostream& os, const Entity& dude);
    friend class Potion;
    int get_current_health();
    bool accept_visit(visitor_alive vis);

};
