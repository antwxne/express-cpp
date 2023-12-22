/*
** EPITECH PROJECT, 2024
** Basic_server
** File description:
** Created by antoine,
*/

#ifndef BASIC_SERVER_DEBUG_HPP
#define BASIC_SERVER_DEBUG_HPP

#include "Exceptions/MyException.hpp"

class Debug {
public:
    static void log(const std::string &str) noexcept;
    static void warn(const std::string &str) noexcept;
    static void err(const std::string &str) noexcept;

    static void log(const MyException &e) noexcept;
    static void warn(const MyException &e) noexcept;
    static void err(const MyException &e) noexcept;
};

#endif //BASIC_SERVER_DEBUG_HPP
