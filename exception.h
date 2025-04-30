#pragma once

#include "libraryes.h"

class MyException : public std::exception
{
public:
	virtual const char* what() const throw() override = 0;
};

class Input_NAN: public MyException
{
public:
	const char* what() const throw() override {
		return "Input must be numeric!";
	}
};
class Input_too_low: public MyException
{
public:
	const char* what() const throw() override {
		return "Value is too low!";
	}
};
class Input_too_high: public MyException
{
public:
	const char* what() const throw() override {
		return "Input is too high!";				
	}
};
class Input_Invalid: public MyException
{
public:
	const char* what() const throw() override {
		return "Invalid input!";
	}
};