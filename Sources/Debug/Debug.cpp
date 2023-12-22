/*
** EPITECH PROJECT, 2024
** Basic_server
** File description:
** Created by antoine,
*/

#include "Debug.hpp"

#ifdef DEBUG

#include <iostream>

static const char *ORANGE = "\033[38;5;208m";

static const char *RED = "\033[38;5;1m";

static const char *GREEN = "\033[32m";

static const char *RESET = "\033[0m";

static const char *BOLD = "\033[1m";

static const char *UNDERLINED = "\033[4m";

void Debug::log(const std::string &str) noexcept
{
    std::cerr << GREEN << "[LOG] " << RESET << str << std::endl;
}

void Debug::warn(const std::string &str) noexcept
{
    std::cerr << ORANGE << BOLD << "[WARNING] " << RESET << str << std::endl;
}

void Debug::err(const std::string &str) noexcept
{
    std::cerr << RED << UNDERLINED << BOLD << "[ERROR]"<< RESET << " " << str
        << std::endl;
}

void Debug::log(const MyException &e) noexcept
{
    std::cerr << GREEN << "[LOG]" << RESET << e << std::endl;
}

void Debug::warn(const MyException &e) noexcept
{
    std::cerr << ORANGE << BOLD << "[WARNING] " << RESET << e << std::endl;
}

void Debug::err(const MyException &e) noexcept
{
    std::cerr << RED << UNDERLINED << BOLD << "[ERROR]" << RESET << " "  << e << std::endl;
}

#else

void Debug::log(const std::string &str) noexcept
{
}

void Debug::warn(const std::string &str) noexcept
{
}

void Debug::err(const std::string &str) noexcept
{
}

void Debug::log(const MyException &str) noexcept
{
}

void Debug::warn(const MyException &str) noexcept
{
}

void Debug::err(const MyException &str) noexcept
{
}

#endif //DEBUG