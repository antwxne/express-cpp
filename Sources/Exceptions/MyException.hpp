/*
** EPITECH PROJECT, 2024
** Basic_server
** File description:
** Created by antoine,
*/

#ifndef BASIC_SERVER_MYEXCEPTION_HPP
#define BASIC_SERVER_MYEXCEPTION_HPP

#include <string>
#include <exception>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

class MyException : std::exception {
public:
    MyException(const std::string &what, const std::string &function,
        const std::string &file, int line
    );
    const char *what() const noexcept override;
    const char *where() const noexcept;
    const char *whichFunction() const noexcept;
    const char *whichFile() const noexcept;
    const char *whichLine() const noexcept;

private:
    std::string _what;
    std::string _func;
    std::string _file;
    std::string _line;
    std::string _where;
};

std::ostream &operator<<(std::ostream &os, const MyException &exception);

#endif //BASIC_SERVER_MYEXCEPTION_HPP
