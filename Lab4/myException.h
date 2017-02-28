// myException.h
// Author: Jennie Liu    jiayiliu@wustl.edu     Zhihao Rong		zrong@wustl.edu
// Definition of the exceptions
#pragma once
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <string>
#include <exception>
#include <stdexcept>

class instance_not_available : public exception
{
public:
	explicit instance_not_available() : exception() { }
};

class game_already_started : public exception
{
public:
	explicit game_already_started() : exception() { }
};

class unknown_game : public exception
{
public:
	explicit unknown_game() : exception() { }
};

class no_game_in_progress : public exception
{
public:
	explicit no_game_in_progress() : exception() { }
};

class already_playing : public exception
{
public:
	explicit already_playing() : exception() { }
};
#endif