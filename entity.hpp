#pragma once

#include <iostream>
#include <iomanip>
#include <string>

class Potion; 

class Entity {
protected:
    int level, damage, health, current_health, current_damage;
    int coefficient_damage, coefficient_health;
    std::string name;
    bool player;

public:
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
};
