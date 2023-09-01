#include "Utils.hpp"

const char* Utils::intToString(int integer, const char* appendText)
{
    std::string str = std::to_string(integer);
    str.append(appendText);
    const char* a = str.c_str();
    return a;
}