/*
** EPITECH PROJECT, 2024
** Basic_server
** File description:
** Created by antoine,
*/

#include "MyException.hpp"

#ifndef FUNCTION_NAME // from https://stackoverflow.com/questions/15305310/predefined-macros-for-function-name-func
    #ifdef WIN32   //WINDOWS
        #define FUNCTION_NAME   __FUNCTION__
    #else          //*NIX
        #define FUNCTION_NAME   __func__
    #endif
#endif
#ifndef MyExceptionDefault
    #define MyExceptionDefault FUNCTION_NAME, __FILE__, __LINE__
#endif

MyException::MyException(const std::string &what, const std::string &function,
    const std::string &file, int line
) : _what("what: " + what), _func("function: " + function),
    _file("file: " + file), _line("line: " + std::to_string(line)),
    _where("In: " + _file + ", in " + _func + ", at " + _line)
{
}

const char *MyException::what() const noexcept
{
    return _what.c_str();
}

const char *MyException::where() const noexcept
{
    return _where.c_str();
}

const char *MyException::whichFunction() const noexcept
{
    return _func.c_str();
}

const char *MyException::whichFile() const noexcept
{
    return _file.c_str();
}

const char *MyException::whichLine() const noexcept
{
    return _line.c_str();
}

std::ostream &operator<<(std::ostream &os, const MyException &exception)
{
    os << exception.what() << ", " << exception.where();
    return os;
}