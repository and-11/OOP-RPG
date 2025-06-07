#include "item.hpp"

Item::Item() = default;

Item::Item(const std::string& s) : name{s} {}

std::string Item::get_name() const {
    return name ;
}

void Item::print(std::ostream& os) const {
    os << name;
}

std::ostream& operator<<(std::ostream& os, const Item& i) {
    os << "\033[36m";
    i.print(os);
    os << "\033[0m";
    return os;
}