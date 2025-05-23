#include "entity.hpp"

Entity::Entity() : name{"Forgotten"} {
    current_health = 0;
    current_damage = 0;
    coefficient_damage = 0;
    coefficient_health = 0;
    level = damage = health = 0;
    player = false;
}

Entity::Entity(int level, int damage, int health, const std::string& name, int c_damage, int c_health):
    level(level),
    damage(damage),
    health(health),
    current_health(0),
    current_damage(0),
    coefficient_damage(c_damage),
    coefficient_health(c_health),
    name(name),
    player(false) 
    {}

Entity::Entity(const Entity& other) : name(other.name) {
    level = other.level;
    damage = other.damage;
    health = other.health;
    current_health = other.current_health;
    current_damage = other.current_damage;
    coefficient_damage = other.coefficient_damage;
    coefficient_health = other.coefficient_health;
    player = other.player;
}

Entity& Entity::operator=(const Entity& other) {
    level = other.level;
    damage = other.damage;
    health = other.health;
    current_health = other.current_health;
    current_damage = other.current_damage;
    coefficient_damage = other.coefficient_damage;
    coefficient_health = other.coefficient_health;
    player = other.player;
    name = "Cheap_coppy";
    return *this;
}

bool Entity::is_alive() const {
    return current_health > 0;
}

bool Entity::is_player() const {
    return player;
}

int Entity::get_damage() const {
    return current_damage;
}

void Entity::Ready() {
    current_damage = damage + coefficient_damage * level;
    current_health = health + coefficient_health * level;
}

std::string Entity::get_name() const {
    std::string beg, end = "\033[0m";
    beg = is_player() ? "\033[32m" : "\033[31m";
    return beg + name + end;
}

std::string Entity::show_damage() const {
    std::string beg, end = "dmg\033[0m";
    beg = is_player() ? "\033[32m" : "\033[31m";
    return beg + std::to_string(current_damage) + end;
}

void Entity::recive_damage(int value) {
    current_health -= value;
}

std::ostream& operator<<(std::ostream& os, const Entity& dude) {
    std::string beg, end = "\033[0m", dmg = " dmg:", hp = " hp:", lvl = " lvl:";
    beg = dude.is_player() ? "\033[32m" : "\033[31m";

    os << beg + dude.get_name() + lvl + std::to_string(dude.level)
       << std::setw(10) << dmg + std::to_string(dude.current_damage) + hp + std::to_string(dude.current_health)
       << end;

    return os;
}
