#pragma once

#include "entity.hpp"
#include <string>
#include <iostream>

class Item {
protected:
    std::string name;

public:
    Item();
    explicit Item(const std::string& s);
    virtual ~Item() = default;

    virtual void use(Entity& dude) = 0;

    [[nodiscard]] std::string get_name() const;

    virtual void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Item& i);
};
