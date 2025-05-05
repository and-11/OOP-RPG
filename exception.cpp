#include "exception.hpp"

const char* Input_NAN::what() const noexcept {
    return "Input must be numeric!";
}

const char* Input_too_low::what() const noexcept {
    return "Value is too low!";
}

const char* Input_too_high::what() const noexcept {
    return "Input is too high!";
}

const char* Input_Invalid::what() const noexcept {
    return "Invalid input!";
}
