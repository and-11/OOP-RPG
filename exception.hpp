#pragma once

#include <exception>

class MyException : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override = 0;
};

class Input_NAN : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

class Input_too_low : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

class Input_too_high : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};

class Input_Invalid : public MyException {
public:
    [[nodiscard]] const char* what() const noexcept override;
};
