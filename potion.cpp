#include "potion.hpp"

Potion::Potion() : damage_increase{0}, health_increase{0} {}

Potion::Potion(const std::string& name, int damage_i, int health_i)
    : Item{name}, damage_increase{damage_i}, health_increase{health_i} {}

void Potion::use(Entity& dude) {
    dude.current_damage += damage_increase;
    dude.current_health += health_increase;
    std::cout << get_name() << " used on " << dude.get_name() << "\n";
    std::cout << dude << "\n";
}

void Potion::print(std::ostream& os) const {
    os << get_name() << ": " << damage_increase << " damage output increase and "
       << health_increase << " bonus health";
}
